#pragma once
#include<iostream>
#include<string>
#include<set>
#include"Simple_window.h"
#include"Graph.h"
#define Bag_scene 12
#define item_change
/******************************lock������********************************/
class swinglock
{
private:
	int num;
public:
	swinglock() { num = 0; }
	void touch() { if (num == 9) num = 0; else num++; }
	int getnum() { return num; }
};

class doorlock
{
private:
	int numroot;//Ҫ������ָ�
	std::set<int> num_choose;
public:
	doorlock(int numroot);
	bool add_num(int num) { num_choose.insert(num); }
	void remove_num(int num) { num_choose.erase(num); }
	bool check_open() { if (this->numroot_cal() == numroot) return 1; else return 0; };
	int numroot_cal();
};

class Boxblock 
{
private:
	std::vector<swinglock*> lock;
	std::vector<int> code;
	int condition;//0��ʾ����״̬��1��ʾ�������״̬��2��ʾ����״̬
public:
	Boxblock(std::vector<int> code);
	int condition_get() { return condition; }
	void condition_set() { condition++; }
	swinglock* getlock(int num) { return lock[num]; }
	bool checklock();
};

/******************************��Ʒ������********************************/
class item 
{
private:
	int item_thumbnail;
	std::string item_name;
	int item_picture;
	int item_chosen;//ѡ����Ʒ�ı�ʾ
	int item_search;//������Ʒ�ĶԻ�
public:
	item();
	int get_item_thumbnail() { return item_thumbnail; }
	std::string get_item_name() { return item_name; }
	int get_item_picture() { return item_picture; }
};

/*****************************�������interface�Ŀ���******************************/

class interface_change
{
protected:
	int new_scene;
	int get_item;
	int lose_item;
	bool item_chosen_remove;
public:
	interface_change(int nc=-1, int gi=-1, int li=-1,bool icr=0) :new_scene(nc), get_item(gi), lose_item(li),item_chosen_remove(icr) {};
	friend class interface;
	friend class trigger;
};

class scene_change : public interface_change
{
	int trigger_added;
	bool trigger_remove;
public:
	scene_change(bool tr = 0, int ta = -1, int nc = -1, int gi = -1, int li = -1, bool icr = false) :trigger_remove(tr),trigger_added(tr) ,interface_change(nc, gi, li, icr) {};
	interface_change ic() { return interface_change{ new_scene,get_item,lose_item,item_chosen_remove }; }
	friend class scene;
};

/****************************������***************************************/
enum trigger_type { ORDINARY, END_GAME ,BOXKEY,BOXCODE,CARD_SELECTION,DOOR_LOCK,DIALOGUE};
class trigger
{
private:
	trigger_type type;
	int image;
	int trigger_height, trigger_weight;
	Point trigger_vertex;

	int trigger_condition;
	int target_scene;
	int target_item;
	int data;

public:
	trigger();
	void set_picture(int new_image) { image = new_image; }
	bool in_bound(Point xy) { return (trigger_vertex.x <= xy.x && xy.x <= trigger_vertex.x + trigger_weight) && (trigger_vertex.y <= xy.y && xy.y <= trigger_vertex.y + trigger_height); }
	bool condition_judge(int item_chosen) { if (item_chosen == trigger_condition) return 1; else return 0; }
	void trigger_condition_set(int num) { trigger_condition = num; }
	int get_data() { return data; }
	int get_picture() { return image; }
	scene_change trigger_evt(int item_chosen);
};

/****************************����*******************************************/
class scene
{
private:
	int backstage;//����ͼƬ
	std::vector<int> triggers;//��ÿ����ͨ������0��triggerΪ��Ʒ����1��triggerΪ��������2��triggerΪ�˳���
	/*��Bag_scene,triggers��0,1λ���غ͵��飬2-6Ϊ5����ѡ��Ʒ����7Ϊ�����ͼ*/
public:
	scene(int picture, vector<int> trigger) { backstage = picture; triggers = trigger; }
	void add_trigger(int new_trigger) { triggers.push_back(new_trigger); }
	void remove_triger(int delete_trigger);
	int get_picture() { return backstage; }
	interface_change try_trigger(Point xy, int item_chosen);
	int get_trigger_num() { return triggers.size(); }
	int get_trigger(int n) { return triggers[n]; }
};

/******************************��Ϸ��Ϣ����**********************************/

class interface: public Window
{
private:
	std::vector<int> possessed_item;
	int item_chosen;
	int curent_scene;
	int save_scene;

	void click(Mouse_event &e);
	void redraw_interface();
public:
	interface();
};


/*******************************��Դ����**********************************/


extern std::vector<Image*> images;
extern std::vector<item*> all_item;
extern std::vector<scene* > all_scenes;//0��λΪbag_scene//
extern std::vector<trigger*> all_trigger;
extern std::vector<int> showed_images;
extern doorlock dl;
extern Boxblock rbl;
extern Boxblock bbl;
void source_init();