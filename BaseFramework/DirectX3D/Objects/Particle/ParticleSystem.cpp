#include "Framework.h"

// ������ ������ ���Ϸκ��� ��ƼŬ �����ϱ�
ParticleSystem::ParticleSystem(string file)
{
    LoadData(file); // �Ű������� �����Ͽ� ���Ϸκ��� ��ƼŬ ������ �����

    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), data.count);

    //��� �غ�
    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();

    blendState[1]->Alpha(false); // ���� �ϴ� ���� (ȥ�� ������ �ɼ� ���� ���� ����)
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // �� ������
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    quad->SetActive(false); // �̹��� �ϴ��� ����
}

// �ؽ�ó ���Ϸκ��� ���� ��ƼŬ �����ϱ�
ParticleSystem::ParticleSystem(wstring file)
{
    LoadData(file); // ���Ϸκ��� ��ƼŬ�� �����͸� �����Ѵ�

    // �ν��Ͻ��� ���� ���� �غ�
    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), data.count);

    //��� �غ�
    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();

    blendState[1]->Alpha(false); // ���� �ϴ� ���� (ȥ�� ������ �ɼ� ���� ���� ����)
    blendState[1]->AlphaToCoverage(true); // ���� �ϴ� ���� (ȥ�� ������ �ɼ� ���� ���� ����)
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // �� ������
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    quad->SetActive(false); // �̹��� �ϴ��� ����
}

ParticleSystem::~ParticleSystem()
{
    delete quad;
    delete instanceBuffer;
    FOR(2) delete blendState[i];
    FOR(2) delete depthState[i];

}

void ParticleSystem::Update()
{
    // ��ƼŬ�� ������Ʈ�Ǵ� ����

    if (!quad->Active()) return; // �׸��� ��Ȱ��ȭ��� ����

    lifeSpan += DELTA; // �����ֱ� ����

    UpdatePhysical(); //������ ���=���� ������Ʈ
    UpdateColor();    //���� ������Ʈ
    quad->UpdateWorld(); //������Ʈ ����� �̹����� �ݿ�

    if (lifeSpan >= data.duration) // ����� ���� �ֱⰡ ��ƼŬ���� ������ ���ӽð��� �ٴٸ���
    {
        if (data.isLoop) Init(); // �ݺ� �ɼ��� ���� ���, �����
        else Stop(); // �ݺ� �ɼ��� ���� ���, ���߱�
    }
}

void ParticleSystem::Render()
{
    if (!quad->Active()) return;

    // �ν��Ͻ� �غ�
    instanceBuffer->Set(1); // 1 : ���ǹ����� ���⵵ ������, ������ �ᱹ ��¿켱����

    quad->SetRender(); //���� ���� �غ� (�̸� �Լ��� ������ ��� ����)
                       // -> �� ���, ���� �غ� �������� ���� �κ��� �־ 
                       //    ���� ���� �߰�

    //��� ���� �غ�
    blendState[1]->SetState();
    //depthState[1]->SetState();

    DC->DrawIndexedInstanced(6, drawCount, 0, 0, 0); // ������ �Ű����� 3���� �ٸ� ������ ������ �صΰ�
                                                     // ���⼱ 0, 0, 0 �ϸ� ���� ���� ���ϴ�
        //DrawIndexedInstanced : �غ�� �ϳ��� ��� �����͸� ���� ������ ���� �ε����� ���� (���۷� �غ��)
        //                       �ݺ��ؼ� ����ϴ� ����� ���
        // �Ű����� : �� ���� �׸� ���� = ����� �ν��Ͻ��� ���� (���� : �� ���� ���� 6����)
        //                              , ����� Ƚ�� (��ο� �� Ƚ����ŭ)
        //                              , ������, ���� (���� �� ���� = ������ ������ ������ �������)
        //                              , �߰� ������ �ڷᰡ �ִٸ� ��� �ִ°� (=�� ������ ����)

    // ���󺹱�
    blendState[0]->SetState();
    depthState[0]->SetState();
}

void ParticleSystem::GUIRender()
{
    quad->GUIRender(); // �׸��� ����׿��� ���
}

void ParticleSystem::SetPos(Vector3 pos)
{
    quad->Pos() = pos;
}

void ParticleSystem::Play(Vector3 pos, Vector3 rot)
{
    //��ƼŬ�� ����
    quad->SetActive(true);

    quad->Pos() = pos;
    quad->Rot() = rot;

    Init(); // ���� �Լ� ȣ�� (��ƼŬ ����)
}

void ParticleSystem::Stop()
{
    quad->SetActive(false); // �׳� ��Ȱ��ȭ�ϰ� ��
}

void ParticleSystem::UpdatePhysical()
{
    // ���� ���� ������Ʈ

    drawCount = 0; // ��ο� �� Ƚ�� �ʱ�ȭ (=��ƼŬ���ٴ� ������ Ȯ�ο�)

    //��¥�� �Ʒ� �ݺ���
    FOR(data.count) //�� ���ڿ� �ڵ� �ݿ�
    {
        if (lifeSpan < particleInfo[i].startTime) continue;
                // ���� �����ֱⰡ ������ ������ ���� ���� �� = ������ ���� �� �� ��

        //�ֱ� ���� ���� ��ƼŬ�� ����
        particleInfo[i].velocity += particleInfo[i].acceleration * DELTA;
                    //�ӷ� ���ؿ� ���ӷ°� �߰� ������ ���ؼ� �ӵ�(���� + ����)�� �����
        particleInfo[i].transform.Pos() += particleInfo[i].velocity
            * particleInfo[i].speed * DELTA; // �ӵ���, �ӷ°�, ����ð��� ��� �ݿ�, ��ġ ����

        particleInfo[i].transform.Rot().z += particleInfo[i].angularVelocity * DELTA;
                                // �ð�/�ݽð� ȸ�� ���� ������ �ݿ�

        //������ �ɼ��� ���� �־��� ���, �׸��� ������ ����� �ǵ���
        //if (data.isBillboard)
        //{
        //    Vector3 tmpRot;
        //    Vector3 c = CAM->Forward();
        //    tmpRot.y = atan2(c.x, c.z);
        //    Vector2 a = { c.x, c.z };
        //    tmpRot.x = atan2(a.Length(), c.y) - XM_PIDIV2;
        //    //tmpRot.x = atanf(a.Length() / c.y);
        //    particleInfo[i].transform.Rot().x = tmpRot.x;
        //    particleInfo[i].transform.Rot().y = tmpRot.y;
        //
        //    //particleInfo[i].transform.Rot().x = atan2(CAM->Forward().z, CAM->Forward().y);
        //    //particleInfo[i].transform.Rot().y = atan2(CAM->Forward().x, CAM->Forward().z);
        //
        //}
        // * �� ī�޶��ΰ� (���Ͱ� �ƴϰ�) -> ���͸� ���� ī�޶�� ������ ���߱⺸��
        //   �̹����� ī�޶�*��* �ٶ󺸰� �ȴ� -> ���� ���忡�� �� ���� 100%��� ������ ���

        //��� �ð��� ���� ���ϱ�
        float t = (lifeSpan - particleInfo[i].startTime) // ����� �ֱ�
            / (data.duration - particleInfo[i].startTime); // ���ӽð�


        // ������ ���� ũ�Ⱑ Ȥ�� �޶����� �ϸ� ����
        particleInfo[i].transform.Scale() =
            Lerp(particleInfo[i].startScale, particleInfo[i].endScale, t);

        particleInfo[i].transform.UpdateWorld(); //���ݱ��� ���� ��ġ, ȸ��, ũ�� ������Ʈ

        //-> ������� �����ϸ� �� �ν��Ͻ��� ���� �ִ� �ɼǿ� ����,
        //   �ش� �ɼ��� �ð��� ���� �ݿ��� Ʈ������ ����� ���� ����ü �ȿ� ����

        // -> �� ����ü�� ������ �ν��Ͻ��� �ִ´�
        instances[drawCount++].transform = // �� ȣ���� ������ ��ο� �� Ƚ���� +1
            XMMatrixTranspose(particleInfo[i].transform.GetWorld());
                                              // ������ ��Ÿ���� ��� �����͸� ����

        // * �ν��Ͻ��� ���� ����ϰ� ���� ����ü�� �ִ� �͵� �����ϰ�,
        //   ��������δ� �� ���� �������̰�����, �������� ����� �� �صΰ�
        //   ���� �ν��Ͻ��� �� ���� ��ġ�� �� �� ������ �������̴�
    }

    // ������� ���� ��ƼŬ�� ���� ������ �ν��Ͻ� ������ ������ ���ŵȴ�
    // ���� ���� �ν��Ͻ� ������ ���ۿ��� �ݿ�
    instanceBuffer->Update(instances.data(), drawCount);
                                            // ������Ʈ Ƚ���� ��ο� �� Ƚ����ŭ��
}

void ParticleSystem::UpdateColor()
{
    float t = lifeSpan / data.duration; // ������ �ϰ� ����, ���� �ð��� ������ �ϰ� �����
                                        // ���� �Լ����� ������, ���⼱ ����

    //���� t�� Ȱ���ؼ� �� ���� ���� ����
    Float4 color;
    color.x = Lerp(data.startColor.x, data.endColor.x, t); // R
    color.y = Lerp(data.startColor.y, data.endColor.y, t); // G
    color.z = Lerp(data.startColor.z, data.endColor.z, t); // B
    color.w = Lerp(data.startColor.w, data.endColor.w, t); // A

    // ������ ������ ���忡 ����
    quad->GetMaterial()->GetData().diffuse = color;
                        //GetData() : �̹��� �����Ϳ� �����ϱ� ���� �Լ�
                        //diffuse : �̹��� �����Ϳ��� ����
}

void ParticleSystem::Init()
{
    // ��ƼŬ �����ϱ�

    // �ɼ� �߿� ȥ�� ������ ���� �־��� ���, ��� ���¿� �ݿ� �ʿ�
    if (data.isAdditive) blendState[1]->Additive(); //ȥ�� ���� ȣ��
    else blendState[1]->Alpha(true); //���� ����ȭ
                                     //(�߰��� �ɼ��� �ٲ� ���� �־ ���⼭ Ȯ�λ��)

    //��� ���� ����

    lifeSpan = 0; // ���� �ֱ�....(�߿��� ������ ����� �ð�) : �Ҹ� ������ duration����
    drawCount = 0; //��ο� �� Ƚ�� (0 �ʱ�ȭ)
    //data.count = particleCount; // Ŭ�������� ��ƼŬ ���� �ɼ� �ٲ� ��� �޾ƿ���
    particleCount = data.count; // Ŭ�������� ��ƼŬ ���� �ɼ� �ٲ� ��� �޾ƿ���


    //data.count�� particleCount�� �޶��ٸ� ���⼭ �ʱ�ȭ
    instances.resize(data.count);
    particleInfo.resize(data.count);

    // ���� �ν��Ͻ��� �ɼ��� ���⼭ ���� (���� ��Ȳ)
    // * Ȥ�� �ٸ� ������ �ɼ��� �ٲ��� �� ���� �����Ƿ� �׷� ���� ������ ����

    for (ParticleInfo& info : particleInfo)
    {

        if (data.isPos == true) //  0 0 0 ���� ������ �ƴ϶��, ��ü���� �ȿ��� ����
        {
            float tmpXY = XMConvertToRadians(RANDOM->Float(0.0f, 360.0f));
            float tmpZ = XMConvertToRadians(RANDOM->Float(0.0f, 360.0f));
            float tmpR = RANDOM->Float(0.0f, data.radius);
            info.transform.Pos() = Vector3(
                cosf(tmpZ) * cosf(tmpXY) * tmpR,
                cosf(tmpZ) * sinf(tmpXY) * tmpR,
                sinf(tmpZ) * tmpR);
            if (data.isDestPos == true) // ��ǥ���� ������ ��ǥ�������� ����
            {
                info.velocity = data.DestPos - info.transform.Pos();
                info.acceleration = RANDOM->RVector3(data.minAcceleration, data.maxAcceleration);
                info.angularVelocity = RANDOM->Float(data.minAngularVelocity, data.maxAngularVelocity);
                //info.speed = 1;
                info.speed = RANDOM->Float(data.minSpeed, data.maxSpeed);
                info.startTime = RANDOM->Float(data.minStartTime, data.maxStartTime);
                info.startScale = RANDOM->RVector3(data.minStartScale, data.maxStartScale);
                info.endScale = RANDOM->RVector3(data.minEndScale, data.maxEndScale);
            }
            else
            {
                info.velocity = RANDOM->RVector3(data.minVelocity, data.maxVelocity);
                info.acceleration = RANDOM->RVector3(data.minAcceleration, data.maxAcceleration);
                info.angularVelocity = RANDOM->Float(data.minAngularVelocity, data.maxAngularVelocity);
                info.speed = RANDOM->Float(data.minSpeed, data.maxSpeed);
                info.startTime = RANDOM->Float(data.minStartTime, data.maxStartTime);
                info.startScale = RANDOM->RVector3(data.minStartScale, data.maxStartScale);
                info.endScale = RANDOM->RVector3(data.minEndScale, data.maxEndScale);

                info.velocity.Normalize();
            }

        }
        else
        {
            info.transform.Pos() = {}; // �ϴ� ���
            if (data.isDestPos == true) // ��ǥ���� ������ ��ǥ�������� ����
            {
                info.velocity = info.transform.Pos() - data.DestPos;
                info.acceleration = RANDOM->RVector3(data.minAcceleration, data.maxAcceleration);
                info.angularVelocity = RANDOM->Float(data.minAngularVelocity, data.maxAngularVelocity);
                info.speed = 1;
                info.startTime = RANDOM->Float(data.minStartTime, data.maxStartTime);
                info.startScale = RANDOM->RVector3(data.minStartScale, data.maxStartScale);
                info.endScale = RANDOM->RVector3(data.minEndScale, data.maxEndScale);
            }
            else
            {
                //�� ��ƼŬ�� ��ü �ɼ� ����
                info.velocity = RANDOM->RVector3(data.minVelocity, data.maxVelocity);
                info.acceleration = RANDOM->RVector3(data.minAcceleration, data.maxAcceleration);
                info.angularVelocity = RANDOM->Float(data.minAngularVelocity, data.maxAngularVelocity);
                info.speed = RANDOM->Float(data.minSpeed, data.maxSpeed);
                info.startTime = RANDOM->Float(data.minStartTime, data.maxStartTime);
                info.startScale = RANDOM->RVector3(data.minStartScale, data.maxStartScale);
                info.endScale = RANDOM->RVector3(data.minEndScale, data.maxEndScale);

                info.velocity.Normalize();
            }

        }
    }
    // -> �ݺ����� ������ ��ƼŬ �ɼǿ� ���� �� �̹����� ���� ���� ����
}

void ParticleSystem::LoadData(string file)
{
    // ������ ������ ������ ���� ��, �ش� ������ �о ��ƼŬ �����ϱ�

    BinaryReader* reader = new BinaryReader(file);

    //�ؽ�ó ���� �̸��� �о����
    wstring textureFile = reader->WString();
    //���� ���� �Ŀ� �ؽ�ó �����ϱ�
    quad = new Quad(Vector2(1, 1));
    quad->GetMaterial()->SetDiffuseMap(textureFile);
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl");

    ParticleData* particleData = new ParticleData();
    reader->Byte((void**)&particleData, sizeof(ParticleData));
    data = *particleData;

    // ��ƼŬ ���� + �����
    // �о���� �����Ϳ� ���� ���� ����
    instances.resize(data.count);
    particleInfo.resize(data.count);

    //delete particleData;
    delete reader;
}

void ParticleSystem::LoadData(wstring file)
{
    // �׸� ���Ͽ��� ���� �����
    quad = new Quad(Vector2(1, 1)); // ǥ�� ũ��� �簢������ �����

    // ���� ���忡 ��Ƽ������ ���� (�׸��� �ٷ� �� ���� ���� : �ٷ� ���� ���� ũ�Ⱑ �׸��� ����)
    quad->GetMaterial()->SetDiffuseMap(file);
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl"); // �⺻ ��ƼŬ ���̴�
                                                             // (�� �⺻���� ������ �ؽ�ó ���̴�)

    //�ɼ����� �����Ǿ��� ������ ���߾ �ν��Ͻ��� ����(=���� ���� �� ������� ����)
    //instances.resize(data.count); // ������ ���� �ɼ��� ����� ���
    instances.resize(particleCount); // Ŭ������ ��� ������ ����� ���
                                     // ���� �Լ������� �� �� ��� data.count�� �� ��
                                     // (��ƼŬ�μ��� �ɼ��� �Ἥ)

    //�ν��Ͻ��� ���� ���͵� �ʱ�ȭ
    //particleInfo.resize(data.count);
    particleInfo.resize(particleCount);

    // -> �׸� ���Ͽ��� ���� ���� + �ν��Ͻ� ���� + ��ƼŬ�� ����Ʈ �ɼ� �ε� �Ϸ�
}