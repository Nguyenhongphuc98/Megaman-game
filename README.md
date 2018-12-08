# Game

Name: MegamanX3
Team:
      -Nguyễn Hồng Phúc- team leader.
      -Nguyễn Quang Nghĩa - member.

API: DirectX (june).
Language: C++.
IDE: Visual studio

Game have three main part:
- Process Input: All event from input can be process .
- Update: Update all Object (megaman, virtual Object, enemy, bullet, item) - location, collision, state.
- Render: Show graphic to screen.

1. Object:
- The class used to inherit, contains the full attribute 1 possible object.
2. ActionObject:
- All animated objects are treated as actionObject.
3. VirtualObject:
- Object static as ground, wall,...
4. Megaman:
- inherit from ActionObject.
- have animation state, charing, lifebar.
- Update - with virtual object. tu stand/ jump,..
- Process with Bullet: -with enemy, being hurting, and set state bullet to destroy when collision.
