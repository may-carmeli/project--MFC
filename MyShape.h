#pragma once
class MyShape : public CObject
{
public:
	CPoint start, end;
	DECLARE_SERIAL(MyShape)
	MyShape();
	virtual ~MyShape(void);
	void setStart(CPoint p) { start = p; }
	void setEnd(CPoint p) { end = p; }
	// for select object and move
	bool IsContained(CPoint p);
	//
	CPoint getStart() const { return start; }
	CPoint getEnd() const { return end; }
	COLORREF getBg() const { return bgColor; }
	void setBg(COLORREF c) { bgColor = c; }
	virtual void draw(CDC *dc);
	virtual void innerDraw(CDC *dc) {}
	void Serialize(CArchive& archive);
protected:
	COLORREF bgColor;
};

