#include "Framework.h"

Tree::Tree(Transform* transform, bool one) :transform(transform) ,isOne(one)
{
	collider = new CapsuleCollider();

	collider->SetParent(transform);
	collider->Scale() *= 100.0f;
	collider->Rot().x = XM_PIDIV2;

	test = new Equipment(1);
	test2 = new Equipment(2);
	test3 = new Ingredient(2);
	test4 = new Equipment(3);

	if (isOne)
	{
		impostor = new Quad(Vector2(1920.0f, 1080.0f) * 0.01f);
	}
	else
	{
		impostor = new Quad(Vector2(1920.0f, 1080.0f)*0.0275f);
	}

	FOR(2)
	{
		blendState[i] = new BlendState();
	}

	blendState[1]->Alpha(true);
	blendState[1]->AlphaToCoverage(true);

}

Tree::~Tree()
{
	delete collider;
	delete test;
	delete test2;
	delete test3;
	delete test4;

	delete impostor;
	FOR(2)
	{
		delete blendState[i];
	}
}

void Tree::Update()
{
	if (isDead) return;
	SetImpostor();
	impostor->Update();

	//Vector2 dir = CAM->GlobalPos() - 
	if (!transform->Active()) return;

	if (Hp < 0.0f)
	{
		transform->SetActive(false);
		isDead = true;
	}



	GetTem(PlayerManager::Get()->GetPlayer()->GetMiningCol());

	transform->UpdateWorld();
	collider->UpdateWorld();
}

void Tree::Render()
{
	if (isDead) return;

	if (transform->Active())
	{
		collider->Render();
	}
	else
	{
		blendState[1]->SetState();
		impostor->Render();
		blendState[0]->SetState();
	}

}

void Tree::GUIRender()
{
	//ImGui::SliderFloat("height", &height, 0.0f, 14.0f);
}

//void Tree::Place(Transform* transform)
//{
//}

void Tree::Hit()
{
	Hp -= 20.0f;
}

void Tree::GetTem(Collider* collider)
{

	if (this->collider->IsCollision(collider))
	{
		Time += 3 * DELTA;

	}



	if (Time > 5)
	{
		ItemManager::Get()->Mining(test);
		ItemManager::Get()->Mining(test2);
		ItemManager::Get()->Mining(test3);
		ItemManager::Get()->Mining(test4);
		//test2 = nullptr;
		Time = 0;
	}

}

void Tree::SetImpostor()
{
	impostor->Rot().y = CAM->GetParent()->Rot().y + XM_PI;
	eyeDir = PlayerManager::Get()->GetPlayer()->Pos() - transform->Pos();
	//theta = atanf(eyeDir.z / eyeDir.x) + transform->Rot().y + XM_PI;
	//theta = atan2(eyeDir.z , eyeDir.x) + transform->Rot().y + XM_PI;
	theta = atan2(eyeDir.z, eyeDir.x) + transform->Rot().y;

	if (theta > XM_2PI)
	{
		theta -= XM_2PI;
	}

	if (theta < 0.0f)
	{
		theta += XM_2PI;
	}



	if (isOne)
	{
		impostor->Pos() = transform->Pos() + Vector3(0.0f, 20.0f, 0.0f);


		if (theta >= 0.0f * (XM_2PI / 360.0f) && theta < 22.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_0.png");
		}
		else if (theta >= 22.5f * (XM_2PI / 360.0f) && theta < 67.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_45.png");
		}
		else if (theta >= 67.5f * (XM_2PI / 360.0f) && theta < 112.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_90.png");
		}
		else if (theta >= 112.5f * (XM_2PI / 360.0f) && theta < 157.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_135.png");
		}
		else if (theta >= 157.5 * (XM_2PI / 360.0f) && theta < 202.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_180.png");
		}
		else if (theta >= 202.5f * (XM_2PI / 360.0f) && theta < 247.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_225.png");
		}
		else if (theta >= 247.5f * (XM_2PI / 360.0f) && theta < 292.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_270.png");
		}
		else if (theta >= 292.5f * (XM_2PI / 360.0f) && theta < 337.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_315.png");
		}
		else if (theta >= 337.5f * (XM_2PI / 360.0f) && theta < 360.0f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_0.png");
		}
	}
	else
	{
		impostor->Pos() = transform->Pos() + Vector3(0.0f, height, 0.0f);


		if (theta >= 0.0f * (XM_2PI / 360.0f) && theta < 22.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_0.png");
		}
		else if (theta >= 22.5f * (XM_2PI / 360.0f) && theta < 67.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_45.png");
		}
		else if (theta >= 67.5f * (XM_2PI / 360.0f) && theta < 112.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_90.png");
		}
		else if (theta >= 112.5f * (XM_2PI / 360.0f) && theta < 157.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_135.png");
		}
		else if (theta >= 157.5 * (XM_2PI / 360.0f) && theta < 202.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_180.png");
		}
		else if (theta >= 202.5f * (XM_2PI / 360.0f) && theta < 247.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_225.png");
		}
		else if (theta >= 247.5f * (XM_2PI / 360.0f) && theta < 292.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_270.png");
		}
		else if (theta >= 292.5f * (XM_2PI / 360.0f) && theta < 337.5f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_315.png");
		}
		else if (theta >= 337.5f * (XM_2PI / 360.0f) && theta < 360.0f * (XM_2PI / 360.0f))
		{
			impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/TreeImpostor/Tree2/ITree2_0.png");
		}
	}
}
