# Game

Name: MegamanX3 <br>
Team:<br>
- Nguyễn Hồng Phúc- team leader.<br>
- Nguyễn Quang Nghĩa - member.<br>
<br>
API: DirectX (june).<br>
Language: C++.<br>
IDE: Visual studio<br>
<br>

Game have three main part:
- Process Input: All event from input can be process .
- Update: Update all Object (megaman, virtual Object, enemy, bullet, item) - location, collision, state.
- Render: Show graphic to screen.
<br>
List Class and Function:
- Object:
+ The class used to inherit, contains the full attribute 1 possible object.<br>
<br>
- ActionObject:
+ All animated objects are treated as actionObject.<br>
- VirtualObject:
+ Object static as ground, wall,...<br>
<br>
- Megaman:
+ inherit from ActionObject.<br>
+ have animation state, charing, lifebar.<br>
+ Update - with virtual object. tu stand/ jump,..<br>
+ Process with Bullet: -with enemy, being hurting, and set state bullet to destroy when collision.<br>
