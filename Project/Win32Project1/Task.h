#pragma once

class Task{
public:
	virtual ~Task(){}
	virtual void Initialize(){}
	virtual void Finalize(){}
	virtual void Update(){}	//�K���p����Ŏ�������
	virtual void Draw(){}	//�K���p����Ŏ�������
};