# 2d_drawing
postech graphics assignment#1

OpenGL을 이용하여 구현한 간단한 탄막 슈팅 게임. 고전적인 2d 슈팅 게임과 룰을 동일시 한다. 내가 총알을 맞으면 체력이 깎이고, 적이 총알을 맞으면 체력이 깎이고 다른 새로운 적이 나오는 시스템이다.

<img src=".images/playing_scene.png" width="300" height="300">

## 1. Environment
clang 12.0.0 (or Visual Studio 2019)
OpenGL 4.6
FreeGLUT 3.0.0
GLEW 2.1.0
Glm 0.9.8.5


## 2. 실행 방법
아래 그림과 같이 Makefile과 main.cpp, mode.h, objects.h가 디렉토리에 존재하는지 확인한 후, 명령어 make를 입력한다.

<img src=".images/make.png">

make 실행 후 아래와 같이 2d_drawing.out이 생성된다.

<img src=".images/after_make.png">

2d_drawing.out를 실행시키면 게임이 시작된다.

<img src=".images/execution.png">

프로그램 시행 시, 바로 게임이 실행된다.키보드로 플레이어의 비행체를 조종하며 스페이스바를 이용해 총알을 발사할 수 있다. 플레이어의 체력이 다 닳으면 LOSE, 모든 적의 체력을 깎으면 WIN이 화면에 표시된다.

## 3. Design
class를 이용해 게임 내 물체들을 나타내었다. 
이때 각각의 물체를 나타내는 class들은 모두 하나의 클래스(Object)으로 부터 inherit한 class이다.

### Object
#### Features
- ***shape***: 해당 object의 모양, 크기와 위치를 나타낸다. shape의 data type이 모양(사각형, 삼각형)을 결정하며, shape이 저장하고 있는 값(x, y좌표, width, height)이 위치와 크기를 나타낸다. 
#### Interface
- ***get_shape***: 해당 unit의 shape를 가리키는 포인터를 return
- ***move_up***: float형 값을 인자로 받아, 그 크기만큼 unit을 위로 이동한 후, 이동 후 위치를 return한다. 만약 이동 예정 위치가 경계를 벗어날 경우, 그 작업을 시행하지 않는다. (move_down, move_right, move_left는 방향을 제외한 효과는 같다.)

### Player
#### Features
- ***hp***: 플레이어의 체력을 나타낸다. 생성 시, 3으로 초기화된다.
#### Interface
- ***getHP***: 플레이어의 체력을 return.
- ***hit***: 플레이어가 총알에 맞았을 경우 실행된다. 게임모드(NORMAL, ALLPASS, ALLFAIL)에 따라 다른 효과가 실행된다. 
  - NORMAL: hp를 1 감소시킨다.
  - ALLPASS: 아무런 동작을 실행하지 않는다.
  - ALLFAIL: hp를 0으로 설정한다. 

### Enemy
#### Features
- ***hp***: 적의 체력을 나타낸다.
#### Interface
- ***getHP***: 적의 체력을 return.
- ***hit***: 적이 총알에 맞았을 경우 실행된다. 게임모드(NORMAL, ALLPASS, ALLFAIL)에 따라 다른 효과가 실행된다. 
  - NORMAL: hp를 1 감소시킨다.
  - ALLPASS: hp를 1로 설정한다.
  - ALLFAIL: hp를 1 감소시킨다.
   
  해당 효과 실행 후, 체력이 0 이하가 되었을 경우 false 그렇지 않다면 true를 return 한다.
  
### EnemyList
#### Features
- ***enemy_list***: Enemy object들의 vector
- ***index***: 현재 Enemy의 index
- ***total_num***: Enemy들의 총 개수
#### Interface
- ***getEnemy***: 현재 index가 가리키는 Enemy를 return.
- ***getIndex***: 현재 index를 return.
- ***hit***: 현재 index가 가리키는 Enemy의 hit()함수를 호출하여 hp를 감소시킨다. 만약 그 enemy의 체력이 0이 되었을 경우(false를 return) index를 1 추가시킨다. index가 total_num과 같아졌을 경우 ***구현 예정***

### Bullet
#### Features
#### Interface

### BulletList
#### Features
- ***bullet_list***: bullet들의 vector
#### Interface
- ***shoot***: bullet_list에 bullet object를 하나 만들어서 추가. 플레이어의 bullet인지에 대한 여부를 인자로 받아, player 혹은 enemy의 위치를 받아온다. 이를 바탕으로 bullet object를 생성하여 bullet_list에 추가한다.
- ***move_bullets***: direction을 인자로 받아, 해당하는 방향으로 bullet_list의 모든 bullet을 이동시킨다. 만약 적 혹은 플레이어의 boundary 안에 총알이 위치할 경우, enemy_list.hit 혹은 player.hit을 호출한다.
- ***get_bullet_shapes***: 모든 bullet의 shape를 vector에 저장한 후, return한다.

## 4.Discussion

고민했던 부분은 적의 움직임 패턴과 히트박스, 즉 적과 플레이어의 비행체의 어느 부분에 맞아야 체력이 깎이도록 설정하냐는 것이었다.
첫번째로 적의 움직임에 관해서, 좌우로 한정적으로 밖에 움직일 수 없기 때문에 거론된 것은 일정하게 좌우로 끝까지 움직이기, 일정한 주기로 랜덤하게 움직일 방향을 정하기, 플레이 화면의 가운데를 축으로 플레이어와 대칭된 x 좌표로 움직이기 등 다양한 의견이 나왔다. 그 중 채용된 것은 일정하게 좌우로 끝까지 움직이는 패턴과 일정한 주기로 랜덤하게 움직일 방향을 정하는 것이었는데, 적마다 다양성을 주기 위해 각각 어느 방향으로 갈지에 대한 확률을 달리 하였다.
두 번째는 적과 플레이어의 비행체의 어느 부분에 총알이 닿아야 체력이 깎이도록 설정하냐, 즉 히트 박스에 관한 것이다. 아무래도 고전적인 슈팅 게임을 지향하기에 히트 박스에 대해서도 고전적으로 진행하였다.

<png src=".images/hitbox.png>

검은 삼각형이 비행체이고, 빨간 테두리가 히트 박스이다. 비행체의 WIDTH와 HEIGHT는 모두 알파로 표기하였으며 실제값은 0.15이다. 비율로 표기하기 위해 알파를 사용하였다. 저 빨간 히트 박스 안에 총알의 중심이 맞아야 체력이 깎이며, 이 때 각 비행체의 hit() method가 불린다.
그 외 기존에 적용한 단순 translation을 지우고 수업시간에 배운 glLoadIdentity, glRotatef, glTranslatef를 적용해보면서 익숙해지는 시간을 가졌다.

