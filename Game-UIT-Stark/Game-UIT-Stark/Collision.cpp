#include"Collision.h"
Collision* Collision::instance;

Collision::Collision()
{
}

Collision::~Collision()
{
}

Collision * Collision::Instance()
{
	if (!instance)
		instance = new Collision();
	return instance;
}

ResultColision Collision::ProcessCollisionSweptAABB(CollisionRect o1, CollisionRect o2)
{
	ResultColision r;
	r.collision = false;
	r.timeToColision = -1.0f;
	r.velocityX = r.velocityY = 0.0f;

	//if (o1.IsIntersect(o2))
	//	Global::Notify("intersec", "check");

	//tinh  du lieu cua o1
	float ml = o1.GetLeft();
	float mt = o1.GetTop();
	float mr = ml + o1.GetWidth();
	float mb = mt + o1.GetHeight();

	//tinh van toc tuong doi
	float dx = o1.GetVelocityX() - o2.GetVelocityX();
	float dy = o1.GetVelocityY() - o2.GetVelocityY();

	//tinh  du lieu cua o2
	float sl = o2.GetLeft();
	float st = o2.GetTop();
	float sr = sl + o2.GetWidth();
	float sb = st + o2.GetHeight();

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;


	//
	// Kiem tra nhanh, neu o bao boi frame hien tai a frame tiep theo
	// của o1 khong giao nhau voi o2 thi chac chan khong co va cham

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return r;
	if (dx == 0 && dy == 0) return r;		// moving object is not moving > obvious no collision

	//tinh theo truc x
	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}

	//tinh theo truc y
	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}


	//tinh ti le cua quang duong thuc su va quang duong du kien theo x ( khong phai la time)
	if (dx == 0)
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	//tinh ti le cua quang duong thuc su va quang duong du kien theo y ( khong phai la time)
	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	//cac TH khong the va cham
	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return r;

	t_entry = std::fmax(tx_entry, ty_entry);
	t_exit = std::fmin(tx_exit, ty_exit);

	//chua va cham da ket thuc
	if (t_entry > t_exit) return r;


	//neu code chay den duoc day tuc la co va cham
	r.timeToColision = t_entry;
	r.collision = true;

	//tinh toan huong va cham
	if (tx_entry > ty_entry)
	{
		r.velocityY = 0.0f;
		dx > 0 ? r.velocityX = -1.0f : r.velocityX = 1.0f;
	}
	else
	{
		r.velocityX = 0.0f;
		dy > 0 ? r.velocityY = -1.0f : r.velocityY = 1.0f;
	}
	return r;
	//ResultColision result;
	//result.collision = false;

	///*Xét trường hợp cả 1 vật đều di chuyển, ta giả sử object2 đứng yên */
	///*bằng cách sử dụng công thức vận tốc tương đối                     */

	////int top1 = object1.GetTop();
	////int left1 = object1.GetLeft();
	////int top2 = object2.GetTop();
	////int left2 = object2.GetLeft();

	//float vx = object1.GetVelocityX() - object2.GetVelocityX();
	//float vy = object1.GetVelocityY() - object2.GetVelocityY();

	//float o1right = object1.GetLeft() + object1.GetWidth();
	//float o1bottom = object1.GetTop() + object1.GetHeight();
	//float o2right = object2.GetLeft() + object2.GetWidth();
	//float o2bottom = object2.GetTop() + object2.GetHeight();

	///* caculate SX to Collision and exit Collision */
	//if (vx > 0.0f) {
	//	this->sXToCollision = object2.GetLeft() - o1right;
	//	this->sXToEndCollision = o2right - object1.GetLeft();
	//}
	//else
	//{
	//	this->sXToCollision = o2right - object1.GetLeft();
	//	this->sXToEndCollision = object2.GetLeft() - o1right;
	//}

	///* caculate SY */
	//if (vy > 0.0f)
	//{
	//	this->sYToCollision = object2.GetTop() - o1bottom;
	//	this->sYToEndCollision = o2bottom - object1.GetTop();
	//}
	//else
	//{
	//	this->sYToCollision = o2bottom - object1.GetTop();
	//	this->sYToEndCollision = object2.GetTop() - o1bottom;
	//}

	///* tính thời gian để xảy ra va chạm theo X	*/

	//if (vx == 0.0f)
	//{
	//	this->tXToCollision = -std::numeric_limits<float>::infinity(); //am vo cuc
	//	this->tXToEndCollision = std::numeric_limits<float>::infinity();
	//}
	//else
	//{
	//	this->tXToCollision = this->sXToCollision / (vx);
	//	this->tXToEndCollision = this->sXToEndCollision / (vx);
	//}

	///* tính thời gian để xảy ra va chạm theo Y	*/
	//if (vy == 0.0f)
	//{
	//	this->tYToCollision = -std::numeric_limits<float>::infinity();
	//	this->tYToEndCollision = std::numeric_limits<float>::infinity();
	//}
	//else
	//{
	//	this->tYToCollision = this->sYToCollision / (vy);
	//	this->tYToEndCollision = this->sYToEndCollision / (vy);
	//}

	///* tính toán kết quả của va chạm */


	///*cả 2 trục va chạm thì va chạm mới chính xác là xảy ra */
	///*1 trong 2 kết thúc thì va chạm kết thúc               */

	//this->timeToCollision = std::fmax(this->tXToCollision, this->tYToCollision);
	//this->timeToEndCollision = std::fmin(this->tXToEndCollision, this->tYToEndCollision);

	//result.timeToColision = 1.0f;
	///* trường hợp không có va chạm */
	//if (this->timeToCollision > this->timeToEndCollision //chưa va chạm đã kết thúc
	//	|| (this->tXToCollision < 0.0f && tYToCollision < 0.0f) //time va chạm <0
	//	|| this->tXToCollision > 1.0f
	//	|| this->tYToCollision > 1.0f) //time va chạm >1 thì xem như k có mà mình sẽ chỉ xét ở frame kế tiếp
	//{
	//	result.velocityX = 0.0f;
	//	result.velocityY = 0.0f;
	//}
	//else /* Có va chạm */
	//{
	//	result.timeToColision = this->timeToCollision;
	//	result.collision = true;
	//	/* va chạm theo Y trước -> trái hoặc phải*/
	//	if (this->tXToCollision > this->tYToCollision)
	//	{
	//		result.velocityY = 0.0f;
	//		//sx
	//		if (sXToCollision < 0.0f)
	//			result.velocityX = 1.0f;
	//		else
	//			result.velocityX = -1.0f;
	//	}
	//	else /* va chạm theo X trước -> trên hoặc dưới*/
	//	{
	//		result.velocityX = 0.0f;
	//		//sy
	//		if (sYToCollision < 0.0f)
	//			result.velocityY = 1.0f;
	//		else
	//			result.velocityY = -1.0f;
	//	}
	//}

	//return result;
}	
