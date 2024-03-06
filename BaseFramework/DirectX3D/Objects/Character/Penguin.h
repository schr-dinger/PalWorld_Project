#pragma once
class Penguin : public Pal
{
private:
    enum class ACTION
    {
        IDLE,
        WALK,
        RUN,
        ATTACK,
        DAMAGE,
        WORK
    };

public:
    Penguin(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
    ~Penguin();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();
    Texture* GetTexture() { return icon; }
    float GetCurHp() { return curHP / maxHP; }

    // 액션 : 공격
    void Attack();      // 내 팔 공격
    void FieldAttack(); // 필드 팔 공격

    // 액션 : 얻어맞기
    void Damage();

    // 액션 : 생성되기
    void Spawn(Vector3 pos);

    // 소환하기 : 플레이어가 팔 소환용
    void Summons(Vector3 pos);


    //표적 설정
    void SetTarget(Transform* target);

    Transform* GetTransform() { return transform; }
    CapsuleCollider* GetCollider() { return collider; }

private:
    //void ClipSync(); // 삭제해도 무방할듯
    
    void SetEvent(int clip, Event event, float timeRatio);
    void ExecuteEvent();

    // 동작 끝나면 실행하는 함수(소환, 사망 모션 필요)
    //void EndStandUp();
    void EndAttack();
    void EndDamage(); // Hit 였으나 enum과 명칭 일치시키기
                      // -> 맞은 모션 후 무엇을 할 것인가
    //void EndDying();

    void SetAction(ACTION action);

    void Move();
    void UpdateUI(); //캐릭터 UI가 있으면 이후 업데이트

private:
    //여기부터
    Transform* transform;
    CapsuleCollider* collider;

    ModelAnimatorInstancing* instancing;
    ModelAnimatorInstancing::Motion* motion;

    Transform* root;
    Transform* target;

    float speed; //속력 : 기본 스탯
    float maxHP;
    float curHP;

    Vector3 velocity; //속력 : 실제 움직임

    UINT index; //로봇의 개별 인덱스

    //스테이트 혹은 움직임에 따른 이벤트 지정
    vector<map<float, Event>> totalEvent;
    vector<map<float, Event>::iterator> eventIters;

    // 팔 UI들(정보, 체력 등)
    ProgressBar* hpBar;

    Vector3 barPos; //체력바가 위치할 곳

    //여기까지 공통, 부모에서 물려 받을 것들

    ACTION action = ACTION::IDLE; 
    // -> 부모로 이동 가능, 이동시
    //    라이딩, 작업같은 특수 동작은 enum 뒤로 빼기

    int tmpN;
};

