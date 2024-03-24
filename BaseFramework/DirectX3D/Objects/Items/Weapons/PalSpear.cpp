#include "Framework.h"

PalSpear::PalSpear(Transform* transform) : transform(transform)
{
    transform->Scale() = { 0.02f, 0.02f, 0.02f }; // ũ�� �⺻���� 1
                                      // ���߿� ũ�Ⱑ �ٲ��� �ϸ� �ͼ� �����ϰ�
    transform->Rot().x = XM_PIDIV2;

    terrain = nullptr;
    pal = nullptr;

    collider = new SphereCollider();
    collider->SetParent(transform);

    collider->Scale() = { 7, 7, 7 }; //ũ�� �⺻���� 1.0
    collider->Pos() = {};            //��ġ �⺻�� : �θ� ��ġ

    state = State::THROW;

    // StateHitPal��
    hitPalTime = 0.0f;

    // StateCatching��
    catchingTime = 0.0f;
    shakeNum = 0;
    shakeTime = 0;

    // �� ���
    //renderTarget = new RenderTarget(2048, 2048); // �������� ������ ������ ũ�� ����
    //depthStencil = new DepthStencil(2048, 2048);
    //
    //whitePal = new Quad(Vector2(1280, 720));
    //whitePal->Pos() = { 640, 360, 0 }; // �簢���� (��������)��¦ ���� ���� = ���� ��ġ�� �簢��
    //whitePal->SetTag("WhitePal");
    //Texture* texture = Texture::Add(L"WhitePalTex", renderTarget->GetSRV());
    //// �ǽð����� �����Ǵ� �̹����� �ؽ�óȭ�ؼ� "�Ϸ���"�̶�� �̸�����
    //
    //whitePal->GetMaterial()->SetDiffuseMap(texture);
    ////whitePal->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
    //whitePal->UpdateWorld(); //

    //palSpearParticle = new ParticleSystem("TextData/Particles/PalSpear.fx");
    palSpearParticle = new ParticleSystem("TextData/Particles/PalSpearNotBill1.fx");
    particleTime = 0.0f;

}

PalSpear::~PalSpear()
{
    delete collider;
    delete palSpearParticle;
}

void PalSpear::Update()
{
    //��Ȱ��ȭ �߿��� �� ������
    if (!transform->Active()) return;

    switch (state)
    {
    case PalSpear::State::THROW:
        StateThrow();
        break;
    case PalSpear::State::HITPAL:
        StateHitPal();
        break;
    case PalSpear::State::ABSORB:
        StateAbsorb();
        break;
    case PalSpear::State::CATCHING:
        StateCatching();
        break;
    case PalSpear::State::SUCCESS:
        StateSuccess();
        break;
    case PalSpear::State::FAIL:
        StateFail();
        break;
    default:
        break;
    }

    collider->UpdateWorld();
    Vector3 tmpRot;
    Vector3 c = CAM->Forward();
    tmpRot.y = atan2(c.x, c.z);
    Vector2 a = { c.x, c.z };
    tmpRot.x = atan2(a.Length(), c.y) - XM_PIDIV2;
    //tmpRot.x = atanf(a.Length() / c.y);
    palSpearParticle->GetQuad()->Rot().x = tmpRot.x;
    palSpearParticle->GetQuad()->Rot().y = tmpRot.y;
    palSpearParticle->GetQuad()->Rot().z += 80* DELTA;

    palSpearParticle->Update();
}

void PalSpear::PreRender()
{
    
}

void PalSpear::Render()
{
    if (!transform->Active()) return;

    collider->Render();
    palSpearParticle->Render();

}

void PalSpear::PostRender()
{
    //whitePal->Render();
}

void PalSpear::GUIRender()
{
    //whitePal->GUIRender();
    if (!transform->Active()) return;
    ImGui::Text("Shake : %d", shakeNum);
    ImGui::Text("catchingTime : %f", catchingTime);
}

void PalSpear::Throw(Vector3 pos, Vector3 dir)
{
    //Ȱ��ȭ
    transform->SetActive(true);
    collider->SetActive(true);
    transform->Pos() = pos;
    direction = dir;

    //���⿡ �°� ��(=Ʈ������) ȸ�� ����
    transform->Rot().y = atan2(dir.x, dir.z); //���� ���� + �� ���鿡 ���� ����
    //transform->Rot().y = CAM->Rot().y; //���� ���� + �� ���鿡 ���� ����
                                                          //���� ���� 90�� ���ư� �־���
    //transform->Rot().y = atan2(dir.x, dir.z) - XMConvertToRadians(90);
    //                                           �� ������ ȣ���� �ٲ��ִ� �Լ�

    time = 0; //����ð� ����
    downForce = 0.0f;
    state = State::THROW;
    // StateHitPal��
    hitPalTime = 0.0f;
    // StateCatching��
    catchingTime = 0.0f;
    shakeNum = 0;

    
}

void PalSpear::StateThrow()
{
    downForce += gravi * DELTA;

    Vector3 tmp = (down * downForce);

    transform->Pos() += direction * speed * DELTA;
    transform->Pos() += tmp * DELTA;
    speed -= DELTA * 5;
    if (speed <= 0.0f)
    {
        speed = 0.0f;
        if (transform->Pos().y <= terrain->GetHeight(transform->GlobalPos()))
        {
            transform->Pos().y = terrain->GetHeight(transform->GlobalPos());
            time += DELTA; // �ð� ����� ���� ������ ����
            if (time > LIFE_SPAN)
            {
                transform->SetActive(false);
                speed = 20.0f;
                downForce = 0.0f;
            }
        }
    }
    else if (transform->Pos().y < terrain->GetHeight(transform->GlobalPos()))
    {
        Vector3 normal;
        transform->Pos().y = terrain->GetHeight(transform->GlobalPos(), &normal);
        normal *= -1;
        //Vector3 tmpDir = (direction + tmp.GetNormalized()) * -1;
        Vector3 tmpDir = (direction * speed + tmp) * -1;
        tmpDir = tmpDir.GetNormalized();
        Vector3 tmpD = 2 * normal * (Dot(tmpDir, normal));
        tmpDir *= -1;
        //direction = (tmpDir + tmpD).GetNormalized();
        direction = tmpDir + tmpD;
        //downForce *= -0.6f;
        downForce = 0.0f;
        speed *= 0.8f;
    }
}

void PalSpear::StateHitPal()
{
    hitPalTime += DELTA;
    transform->Pos() += Vector3(0.0f, 1.0f, 0.0f) * 2 * DELTA;  // ����
    transform->Pos() += PlayerManager::Get()->GetPlayer()->Forward() * DELTA; // ������ ���� �ݴ�
    transform->Pos() += PlayerManager::Get()->GetPlayer()->Left() * 2 * DELTA; // ������
    if (hitPalTime > 0.4f)
    {
        state = State::ABSORB;
        hitPalTime = 0.0f;
        pal->GetTransform()->SetActive(false);
        pal->GetCollider()->SetActive(false);

        // ����Ʈ Ȱ��ȭ
        palSpearParticle->Play(pal->GetCollider()->GlobalPos());
        palToPalSpearVel = transform->Pos() - palSpearParticle->GetPos();
    }
}

void PalSpear::StateAbsorb()
{
    // ����Ʈ �� ���Ǿ�� �̵�
    Vector3 tmp = palSpearParticle->GetPos() + palToPalSpearVel * DELTA;
    palSpearParticle->SetPos(tmp);
    particleTime += DELTA;
    if (particleTime >= 1.3f)
    {
        particleTime = 0.0f;
        state = State::CATCHING;
        Float3 tmpPos = transform->GlobalPos();
        SOUND->Stop("Sphere_Shake");
        SOUND->Play("Sphere_Shake", tmpPos);
    }


}

void PalSpear::StateCatching()
{
    catchingTime += DELTA;
    if (catchingTime > 0.5f)
    {
        transform->Rot().x = XM_PIDIV2;
        transform->Rot().y = 0;
        transform->Rot().z = 0;

        if (catchingTime > 1.0f)
        {
            catchingTime = 0.0f;
            shakeNum++;

            if (shakeNum >= 3)
            {
                shakeNum = 0;
                if (RANDOM->Int(0,1) == 0)
                {
                    state = State::SUCCESS;
                }
                else
                {
                    state = State::FAIL;
                }
            }
            else
            {
                Float3 tmpPos = transform->GlobalPos();
                SOUND->Stop("Sphere_Shake");
                SOUND->Play("Sphere_Shake", tmpPos);
            }
        }
        
    }
    else
    {
        float tmpRX = RANDOM->Float(-45.0f, 45.0f);
        float tmpRY = RANDOM->Float(-90.0f, 90.0f);
        float tmpRZ = RANDOM->Float(-20.0f, 20.0f);
        tmpRX = XM_PIDIV2 + XMConvertToRadians(tmpRX);
        tmpRY = XMConvertToRadians(tmpRY);
        tmpRZ = XMConvertToRadians(tmpRZ);
        transform->Rot().x = Lerp(transform->Rot().x, tmpRX, 0.5f);
        transform->Rot().y = Lerp(transform->Rot().x, tmpRY, 0.5f);
        transform->Rot().z = Lerp(transform->Rot().x, tmpRZ, 0.5f);
    }
    
    
}

void PalSpear::StateSuccess()
{
    PlayerPalsManager::Get()->Caught(pal);
    // ���� ����ó��, ���߿� �ٽ� ������ ��
    pal->isDead = true;

    transform->SetActive(false);
    collider->SetActive(false);
    state = State::THROW;
    pal->isInvincible = false;
    Float3 tmpPos = transform->GlobalPos();
    SOUND->Stop("Sphere_Success");
    SOUND->Play("Sphere_Success", tmpPos);
}

void PalSpear::StateFail()
{
    pal->GetTransform()->SetActive(true);
    pal->GetCollider()->SetActive(true);

    transform->SetActive(false);
    collider->SetActive(false);
    state = State::THROW;
    pal->isInvincible = false;

}

void PalSpear::SetRenderTarget()
{
    //renderTarget->Set(depthStencil);
    //renderTarget->Set(depthStencil,Float4(1,1,1,0));

}
