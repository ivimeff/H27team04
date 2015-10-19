#pragma once

class Task{
public:
	virtual ~Task(){}
	virtual void Initialize(){}
	virtual void Finalize(){}
	virtual void Update(){}	//•K‚¸Œp³æ‚ÅÀ‘•‚·‚é
	virtual void Draw(){}	//•K‚¸Œp³æ‚ÅÀ‘•‚·‚é
};