# Game

Name: MegamanX3 <br>
Team:<br>
      -Nguyễn Hồng Phúc- team leader.
      -Nguyễn Quang Nghĩa - member.
<br>
API: DirectX (june).
Language: C++.
IDE: Visual studio
<br>
Game have three main part:
- Process Input: All event from input can be process .
- Update: Update all Object (megaman, virtual Object, enemy, bullet, item) - location, collision, state.
- Render: Show graphic to screen.
<br>
- Object:
+ The class used to inherit, contains the full attribute 1 possible object.
<br>
- ActionObject:
+ All animated objects are treated as actionObject.
- VirtualObject:
+ Object static as ground, wall,...
<br>
- Megaman:
+ inherit from ActionObject.
+ have animation state, charing, lifebar.
+ Update - with virtual object. tu stand/ jump,..
+ Process with Bullet: -with enemy, being hurting, and set state bullet to destroy when collision.
