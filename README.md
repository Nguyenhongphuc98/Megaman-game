# Game

Name: MegamanX3 <br>
Author:<br>
- Nguyễn Hồng Phúc.<br>

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
<br>
List Class and Function:<br>
1.  Object:
- The class used to inherit, contains the full attribute 1 possible object.<br>
<br>
<br>
2.  ActionObject:
- All animated objects are treated as actionObject.
<br>
<br>
3.  VirtualObject:
- Object static as ground, wall,...<br>
<br>
<br>
4.  Megaman:
- inherit from ActionObject.<br>
- have animation state, charing, lifebar.<br>
- Update - with virtual object. tu stand/ jump,..<br>
- Process with Bullet: -with enemy, being hurting, and set state bullet to destroy when collision.<br>
<br>
Image in game:
<img src="https://uphinhnhanh.com/images/2018/12/26/start.png" alt="start.png" border="0" />
<img src="https://uphinhnhanh.com/images/2018/12/26/shuri.png" alt="shuri.png" border="0" />
<img src="https://uphinhnhanh.com/images/2018/12/26/subboss.png" alt="subboss.png" border="0" />
<img src="https://uphinhnhanh.com/images/2018/12/26/blasthornet.png" alt="blasthornet.png" border="0" />
