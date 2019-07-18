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
![image](https://user-images.githubusercontent.com/28861842/61438105-e4184700-a968-11e9-92d0-e973d299fbb1.png)
![image](https://user-images.githubusercontent.com/28861842/61438134-f6928080-a968-11e9-8f5f-b5b8dd437192.png)
![image](https://user-images.githubusercontent.com/28861842/61438155-ff835200-a968-11e9-96cf-08c88d07fbb1.png)
![image](https://user-images.githubusercontent.com/28861842/61438221-26da1f00-a969-11e9-8132-f2ea876e6863.png)
![image](https://user-images.githubusercontent.com/28861842/61438238-30638700-a969-11e9-910a-4a5b811a1aac.png)

