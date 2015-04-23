#pragma once

class Renderable{

protected:
	bool isVisible = false;

public:
	virtual void Render() = 0;
	virtual bool IsVisible(){ return isVisible; };

	virtual void SetVisible(bool visibility){ isVisible = visibility; }
};