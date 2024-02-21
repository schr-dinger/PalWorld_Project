#include "Framework.h"
#include "Rain.h"

Rain::Rain()
{
    //�׸� ����
    material->SetShader(L"Geometry/Rain.hlsl");
    material->SetDiffuseMap(L"Textures/Effect/Rain.png");

    //���̴� ����
    geometryShader = Shader::AddGS(L"Geometry/Rain.hlsl");

    buffer = new WeatherBuffer(); // Ŭ���� �ȿ� �⺻���� ����

    Create();
}

Rain::~Rain()
{
    delete buffer;
}

void Rain::Update()
{
    buffer->Get().time += DELTA; // ����ð��� ����
}

void Rain::Render()
{
    buffer->SetVS(10); // ���� ���� ���࿡ ���� �ɼ� ���� ���� + ���̴� ��µ� ���� ����
    Particle::Render(); // ��ƼŬ�μ� ��� ���� (=����� ���)
}

void Rain::GUIRender()
{
    //���� �ɼ� ����

    ImGui::Text("Rain Effect Option");
    ImGui::DragFloat3("Velocity", (float*)&buffer->Get().velocity, 0.1f);
          //DragFloat3 : ImGUI�� �ɼ� ���� �Լ�, �Ű������� ������ ��ġ, �� ��Ʈ �巡�� �� ����Ǵ� ��ġ
    ImGui::DragFloat3("Origin", (float*)&buffer->Get().origin, 0.1f);
    ImGui::DragFloat3("Size", (float*)&buffer->Get().size, 0.1f);

    ImGui::SliderFloat("Distance", &buffer->Get().distance, 0, 500); // ������ �׷����°�

    ImGui::ColorEdit4("Color", (float*)&buffer->Get().color);
}

void Rain::Create()
{
    int count = 100000; // ���ϴ� ���� �Է�
    buffer->Get().velocity = { 0, -5, 0 }; //�ӷ��� �ʿ��ϸ� ���⼭ ���� (�⺻�� : �Ʒ���)

    particleCount = (count < MAX_COUNT) ? count : MAX_COUNT; // �θ𿡼� ���� �ִ������ �� �Ѵ´�

    vertices.resize(particleCount);
    FOR(particleCount)
    {
        //ũ�� ���ϱ�
        Float2 size;
        size.x = Random(0.1f, 0.4f);
        size.y = Random(2.0f, 8.0f);

        //��ġ ���ϱ�
        Float3 pos;
        pos.x = Random(-buffer->Get().size.x, buffer->Get().size.x); // ũ��� ������ ���� -+ ���� ������
        pos.y = Random(-buffer->Get().size.y, buffer->Get().size.y);
        pos.z = Random(-buffer->Get().size.z, buffer->Get().size.z);
                        // ���� �������� size = ��ƼŬ�μ��� �� ������ ũ��
                        // = ���� ��� ���忡���� "�� ������ ���� ����"
                        // = ������� �ش� ���� ���� ��򰡿� �ִ� ��

        //����� ��ġ�� ���� ���Ϳ� �ݿ�
        vertices[i].pos = pos;
        vertices[i].uv = size; //�̸��� UV�ε� ������ �ϴ� ������ �ؽ�ó�� ũ���� ��
    }

    // ���� ���� ������Ʈ (���� ��)
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), particleCount);
}