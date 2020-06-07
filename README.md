# OpenGLtest
 아마도 타워 디펜스를 만들 예정
## Img Problem
- png로 alpha값 가능하게 해서 크로마키 효과 냄
# Game
## 일단 구조
 - GaemState는 게임의 현재 상태를 enum으로 넣음 State값에 저장
 - game loop
    ### 프로그래머가 해야할 것
    - void ProcessInput(float dt)에 사용될 c라이브러리를 만든다.
    - void Update(float dt)에 사용될 c라이브러리를 만든다.
    ### 디자이너가 해야 할것 (아마)
    - void Render(); 
    - 프로그래머가 넘겨준 c라이브러리로 데이터 연결하기
 - Keys[1024]는 게임 키보드 인풋을 입력 받는다 (모바일 게임 같은거면 안쓸지도)
 - std::vector<GamePage> Pages 이건 게임의 처음 화면 게임 화면 등등의 정보를 받고 있는 vector (디자이너가 합니다)
## 데이터
 - 캐릭터 렌더링 데이터
 - 캐릭터 코딩 데이터
