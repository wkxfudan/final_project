#include "gamecontrol.h"

doorlock::doorlock(int root)
{
	numroot = root;
	num_choose.clear();
}

int doorlock::numroot_cal()
{
	std::set<int>::iterator it;
	int numroot = 0;
	for (it = num_choose.begin(); it != num_choose.end(); it++)
	{
		numroot += *it;
	}
	while (numroot > 9)
	{
		numroot = numroot % 10 + numroot / 10;
	}
	return numroot;
}

void interface::click(Mouse_event &e)
{
	if (curent_scene == Bag_scene)//��������Ĳ���
	{
		scene* bs = all_scenes[curent_scene];
		if (e.pos == Point{ 0,0 })
		{
			curent_scene = save_scene;
			all_trigger[bs->get_trigger(0)]->set_picture(item_chosen);
		}
		else if (e.pos == Point{ 10,0 })
		{
			bs->add_trigger(12);//����Ի��򴥷���
		}
		else//��Ʒ��ѡ��
		{
			int i = 0;
			for (i = 2; i <= 6; i++)
			{
				if (all_trigger[bs->get_trigger(i)]->in_bound(e.pos))
					break;
			}
			if (i == 7)
			{
				return;
			}
			else
			{
				trigger* nowtri = all_trigger[bs->get_trigger(i)];
				nowtri->set_picture(12);//��Ϊ���߿����ƷͼƬ
				item_chosen = nowtri->get_data();//��data�ж�ȡѡ����Ʒ�Ķ�Ӧ��Ʒ
				trigger* big_picture = all_trigger[bs->get_trigger(7)];
				big_picture->set_picture(item_chosen);//���������ͼ��ͼƬ
			}
		}
	}
	else if (e.pos == Point{10, 10})//����������Ʒ���Ĵ���
	{
		scene *cs = all_scenes[curent_scene];
		int i;
		for (i = 0; i < possessed_item.size(); i++)
		{
			if (possessed_item[i] == item_chosen)
				break;
		}
		if (i == possessed_item.size() - 1)
			i = 0;
		else
			i++;
		item_chosen = possessed_item[i];
		all_trigger[cs->get_trigger(0)]->set_picture(i);
	}
	else if (e.pos == Point{ 0,0 })//��Ʒ����ť
	{
		curent_scene = Bag_scene;
		scene* bs = all_scenes[curent_scene];
		int i = 0;
		int j = 0;
		for (i = 2; i <= 6; i++)
		{
			if (j == possessed_item.size())
				break;
			trigger* thistri = all_trigger[bs->get_trigger(i)];
			thistri->set_picture(possessed_item[j]);
			if (item_chosen == possessed_item[j])
			{
				thistri->set_picture(possessed_item[j]);
				all_trigger[bs->get_trigger(7)]->set_picture(possessed_item[j]);
			}//��ѡ����Ʒ������������
			j++;
		}
	}
	else
	{
		interface_change ic = all_scenes[curent_scene]->try_trigger(e.pos, item_chosen);
		if (ic.get_item != -1)
			possessed_item.push_back(ic.get_item);
		if (ic.lose_item != -1)
		{
			std::vector<int>::iterator it;
			for (it = possessed_item.begin(); it != possessed_item.end(); it++)
			{
				if (*it == ic.lose_item)
					break;
			}
			if (*it == item_chosen)
			{
				if ((it + 1) == possessed_item.end())
					item_chosen = *possessed_item.begin();
				else
					item_chosen = *(it + 1);
			}
			possessed_item.erase(it);
		}
		if (ic.new_scene != -1)
		{
			curent_scene = ic.new_scene;
		}
	}
	redraw_interface();
}

void interface::redraw_interface()
{
}

scene_change trigger::trigger_evt(int item_chosen)
{
	if (type == trigger_type::BOXKEY)
	{
		if (item_chosen == trigger_condition)
		{
			if (item_chosen == 6)//��ɫԿ��
			{
				bbl.condition_set();//bbl�����������ת��
				set_picture(0);//�޸Ĵ�����ͼƬΪ����Կ�׵�״̬
				trigger_condition_set(-1);
				return scene_change{ -1,-1,-1,-1,true };
			}
			else if (item_chosen = 7)//��ɫԿ��
			{
				rbl.condition_set();//rbl�����������
				set_picture(0);
				trigger_condition_set(-2);
				return scene_change{ -1,-1,-1,-1,true };
			}
		}
		else if (trigger_condition > 0)
		{
			if (item_chosen != 6 && item_chosen != 7)
			{
				//���������������������
			}
			else
			{
				//���Կ�׺���û��������Կ�׿�
			}
		}
		else//Կ���Ѿ����ϵ�״̬
		{
			if (trigger_condition = -1)//��ɫ����
			{
				if (bbl.checklock())
				{
					bbl.condition_set();//��������
					set_picture(0);//�޸�Կ��Ϊת��������
					return scene_change{ 0,-1,-1,-1,false };
				}
				else
				{
					//Կ���޷�ת���������ƺ�����ȷ
				}
			}
			else
			{
				if (rbl.checklock())
				{
					set_picture(0);
					rbl.condition_set();
					return scene_change{ 0,-1,-1,-1,false };
				}
				else
				{
					//���벻��ȷ
				}
			}
		}
	}
	else if (type == trigger_type::BOXCODE)//����һtype�У�data�洢��λ��������У�trigger_condition�洢��Ӧbox����ɫ
	{
		if (trigger_condition == -1)//��ɫ����
		{
			bbl.getlock(data)->touch();
			int num = bbl.getlock(data)->getnum();
			set_picture(num);
			return scene_change{};
		}
		else//��ɫ����
		{
			rbl.getlock(data)->touch();
			int num = rbl.getlock(data)->getnum();
			set_picture(num);
			return scene_change{};
		}
	}
	else if (type == trigger_type::DOOR_LOCK)
	{
		if (bbl.condition_get == 2 && rbl.condition_get == 2)//�������Ӿ��ѿ���
		{
			//�ǲ���Ҫ�ú�ɫ�ſ������ָ�
			return scene_change{ 0,-1,-1,-1,false };//�л���ѡ�ſ�����
		}
		else
		{
			//���¿��ż���û�з�Ӧ
		}
	}
	else if (type == trigger_type::CARD_SELECTION)
	/*��һtype�°����Ÿ�trigger����tc���������У�123Ϊ��ѡ��Ŀ�Ƭ��4-9Ϊ��ѡ��Ƭ,data����ô�������Ӧ����*/
	{
		if (trigger_condition <= 9 && trigger_condition >= 4)
		{
			bool result = dl.add_num(data);
			if (result == 1)//���뿨Ƭ�ɹ�
			{
				int i = 0;
				for (i = 0; i < 3; i++)
				{
					if (all_trigger[i]->get_data() == -1)
						break;
				}
				all_trigger[i]->set_picture(data);
				return scene_change{ 1,i };
			}
			else
			{
				return scene_change{};
			}
		}
		else
		{
			dl.remove_num(data);
			return scene_change{ 1,data };
		}
	}
	else if (type == trigger_type::ORDINARY)//���������л�����Ʒʰȡ
	{
		if (target_scene == -1)
		{
			return scene_change{ 1,-1,-1,target_item,-1,0 };
		}
		else
		{
			return scene_change{ -1,-1,target_scene,-1,-1,0 };
		}
	}
	else if (type == trigger_type::DIALOGUE)
	{
		return scene_change{ 1,-1,-1,-1,-1.0 };
	}
	else if (type == trigger_type::END_GAME)
	{
		exit(1);
	}
}

void scene::remove_triger(int delete_trigger)
{
	std::vector<int>::iterator it;
	for (it = triggers.begin(); it != triggers.end(); it++)
	{
		if (*it = delete_trigger)
			triggers.erase(it);
	}
}

interface_change scene::try_trigger(Point xy, int item_chosen)
{
	scene_change *sc = NULL;
	int i = 0;
	for (i = 0; i < triggers.size(); i++)
	{
		if (all_trigger[triggers[i]]->in_bound(xy))
		{
			sc = &all_trigger[triggers[i]]->trigger_evt(item_chosen);
			break;
		}
	}
	if (sc != NULL)
	{
		if (sc->trigger_added != -1)
		{
			this->add_trigger(sc->trigger_added);
		}
		if (sc->trigger_remove == 1)
		{
			this->remove_triger(triggers[i]);
		}
		return sc->ic();
	}
	else
	{
		return interface_change{};
	}
}

Boxblock::Boxblock(std::vector<int> input)
{
	code = input;
	lock.push_back(new swinglock{});
	lock.push_back(new swinglock{});
	lock.push_back(new swinglock{});
	lock.push_back(new swinglock{});
}

bool Boxblock::checklock()
{
	bool checkflag = 1;
	for (int i = 0; i < 4; i++)
	{
		if (lock[i]->getnum() != code[i])
			checkflag = 0;
	}
	return checkflag;
}

void interface::redraw_interface()
{
	for (int i = 0; i < showed_images.size(); i++)
	{
		detach(*images[showed_images[i]]);
	}
	showed_images.empty();
	showed_images.push_back(all_scenes[curent_scene]->get_picture());
	scene* cs = all_scenes[curent_scene];
	for (int i = 0; i < cs->get_trigger_num(); i++)
	{
		showed_images.push_back(all_trigger[cs->get_trigger(i)]->get_picture());
	}
	for (int i = 0; i < showed_images.size(); i++)
	{
		attach(*images[showed_images[i]]);
	}
	redraw();
}

void source_init()
{
	/*ͼƬ��ʼ��*/
	Image* pic = new Image{ {0,0},"" };
	images.push_back(pic);

	/*trigger��ʼ��*/
	trigger;

	/*item��ʼ��*/
	item;

	/*scene��ʼ��*/
	scene;
	scene;
	scene;
	scene;
	scene;

	/*��������ĳ�ʼ��*/
	dl = doorlock(5);
	std::vector<int> code = { 1,1,1,2 };
	bbl = Boxblock(code);
	std::vector<int> code = { 1,1,2,2 };
	rbl = Boxblock(code);

	/*showed_image��ʼ��*/
	showed_images.empty();
}
