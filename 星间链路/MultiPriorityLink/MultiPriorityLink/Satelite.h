#pragma once
#include<string>
using namespace std;
class Satelite
{
private:
	//���ǵ�������Ϣ
	string name;			//���ǵ�����
	bool JNX;				//��־�������ھ����ǻ��Ǿ�����
	bool link;				//��־�����Ƿ�����ͨ��
	bool send;				//�����Ƿ�����Ϣ
	bool JL;				//�����Ƿ���
	bool Normal;			//�����Ƿ���������
	bool visit;				//�����Ƿ񱻷��ʹ�
public:
	Satelite();
	~Satelite();
	void SetSateliteName(string);

	bool GetSateliteJNX();
	void SetSateliteJN_JW(bool);

	bool GetSateliteSend();
	void SetSateliteSend(bool);

	bool GetSateliteJL();
	void SetSateliteJL(bool);

	bool GetSatNormal();
	void SetSatNomral(bool);

	bool GetSatVisit();
	void SetSatVisit(bool);
};
