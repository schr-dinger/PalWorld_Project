#include "Framework.h"

Transform::Transform()
{
    world = XMMatrixIdentity();
}

void Transform::UpdateWorld()
{
    world = XMMatrixTransformation(pivot,
        XMQuaternionIdentity(), localScale, pivot,
        XMQuaternionRotationRollPitchYawFromVector(localRotation),
        localPosition);

    if (parent)
        world *= parent->world;

    XMStoreFloat4x4(&matWorld, world);
    right = Vector3(matWorld._11, matWorld._12, matWorld._13);
    up = Vector3(matWorld._21, matWorld._22, matWorld._23);
    forward = Vector3(matWorld._31, matWorld._32, matWorld._33);

    XMVECTOR outS, outR, outT;
    XMMatrixDecompose(&outS, &outR, &outT, world);

    Float3 tempPos, tempScale;
    Float4 tempRot;
    XMStoreFloat3(&tempPos, outT);
    XMStoreFloat3(&tempScale, outS);
    XMStoreFloat4(&tempRot, outR);

    globalPosition = tempPos;
    globalScale = tempScale;   
    //tempRot.x *= XM_PI;
    //tempRot.y *= XM_PI;
    //tempRot.z *= XM_PI;
    //if (parent)
    //    world = parent->world;
    
    //globalRotation = XMQuaternionToAxisAngle;
    SetEul(tempRot.x, tempRot.y, tempRot.z, tempRot.w);
}

void Transform::GUIRender()
{
    if (ImGui::TreeNode((tag + "_Transform").c_str()))
    {
        ImGui::Text(tag.c_str());
    
        ImGui::Checkbox("Active", &isActive);
    
        string temp = tag + "_Pos";
        ImGui::DragFloat3(temp.c_str(), (float*)&localPosition, 0.1f);
    
        temp = tag + "_Rot";
        Float3 rot;
        rot.x = XMConvertToDegrees(localRotation.x);
        rot.y = XMConvertToDegrees(localRotation.y);
        rot.z = XMConvertToDegrees(localRotation.z);
    
        ImGui::DragFloat3(temp.c_str(), (float*)&rot, 1.0f, -180, 180);
    
        localRotation.x = XMConvertToRadians(rot.x);
        localRotation.y = XMConvertToRadians(rot.y);
        localRotation.z = XMConvertToRadians(rot.z);
    
        temp = tag + "_GlobalRot";
        Float3 grot;
        grot.x = XMConvertToDegrees(globalRotation.x);
        grot.y = XMConvertToDegrees(globalRotation.y);
        grot.z = XMConvertToDegrees(globalRotation.z);
        ImGui::DragFloat3(temp.c_str(), (float*)&grot, 1.0f, -180, 180);

        temp = tag + "_Scale";
        ImGui::DragFloat3(temp.c_str(), (float*)&localScale, 0.1f);
    
        if (ImGui::Button("Save"))
            Save();
    
        ImGui::SameLine();
    
        if (ImGui::Button("Load"))
            Load();
    
        ImGui::TreePop();
    }    
}

Transform* Transform::GetParent()
{
    if (parent != nullptr)
        return parent->GetParent();

    return this;
}

bool Transform::Active()
{
    if (parent == nullptr)
        return isActive;

    if (isActive == false)
        return false;

    return parent->Active();
}

void Transform::Save()
{
    BinaryWriter* writer = new BinaryWriter("TextData/Transforms/" + tag + ".srt");

    writer->Float(localPosition.x);
    writer->Float(localPosition.y);
    writer->Float(localPosition.z);

    writer->Float(localRotation.x);
    writer->Float(localRotation.y);
    writer->Float(localRotation.z);
    
    writer->Float(localScale.x);
    writer->Float(localScale.y);
    writer->Float(localScale.z);

    delete writer;
}

void Transform::Load()
{
    BinaryReader* reader = new BinaryReader("TextData/Transforms/" + tag + ".srt");

    if (reader->IsFailed()) return;

    localPosition.x = reader->Float();
    localPosition.y = reader->Float();
    localPosition.z = reader->Float();

    localRotation.x = reader->Float();
    localRotation.y = reader->Float();
    localRotation.z = reader->Float();

    localScale.x = reader->Float();
    localScale.y = reader->Float();
    localScale.z = reader->Float();

    delete reader;
}

void Transform::SetEul(float x, float y, float z, float w)
{
    float t0 = +2.0f * (w * x + y * z);
    float t1 = +1.0f - 2.0 * (x * x + y * y);
    globalRotation.x = atan2(t0, t1);

    float t2 = +2.0f * (w * y - z * x);
    if (std::abs(t2) >= 1)
        globalRotation.y = std::copysign(XM_PI / 2, t2);
    else
        globalRotation.y = std::asin(t2);


    float t3 = +2.0f * (w * z + x * y);
    float t4 = +1.0f - 2.0f * (y * y + z * z);
    globalRotation.z = atan2(t3, t4);
}
