
public class TwiceRectangle implements Rectangle {
	double CX;
	double CY;
	double W;
	double H;
	
	@Override
	public double getCenterX() {
		return this.CX;
	}
	
	@Override
	public double getCenterY() {
		return this.CY;
	}
	
	@Override
	public double getWidth() {
		return this.W;
	}
	
	@Override
	public double getHeight() {
		return this.H;
	}
	
	@Override
	public void setCenterX(double cx) {
		this.CX = cx;
	}
	
	@Override
	public void setCenterY(double cy) {
		this.CY = cy;
	}
	
	@Override
	public void setWidth(double w) {
		this.W = w;
		this.H = w / 2;
	}
	
	@Override
	public void setHeight(double h) {
		this.H = h;
		this.W = 2 * h;
	}
	
	@Override
	public double getPerimeter() {
		return 2 * (this.W + this.H);
	}
	
	@Override
	public boolean intersects(Rectangle r) {
		double c1x = this.CX - this.W / 2;
		double c1y = this.CY - this.H / 2;
		double c2x = c1x + this.W;
		double c2y = c1y + this.H;
		RectangleClass rc = new RectangleClass(r.getCenterX(), 
				r.getCenterY(), r.getWidth(), r.getHeight());
		double c3x = rc.CX - rc.W / 2;
		double c3y = rc.CY - rc.H / 2;
		double c4x = c3x + rc.W;
		double c4y = c3y + rc.H;
		
		if ((c1x >= c4x) || (c2x <= c3x) || (c1y >= c4y) || (c2y <= c3y))
			return false;
		return true;
	}
		
	@Override
	public boolean contains(Rectangle r) {
		double c1x = this.CX - this.W / 2;
		double c1y = this.CY - this.H / 2;
		double c2x = c1x + this.W;
		double c2y = c1y + this.H;
		RectangleClass rc = new RectangleClass(r.getCenterX(), 
				r.getCenterY(), r.getWidth(), r.getHeight());
		double c3x = rc.CX - rc.W / 2;
		double c3y = rc.CY - rc.H / 2;
		double c4x = c3x + rc.W;
		double c4y = c3y + rc.H;
		
		if ((c1x < c3x) && (c2x > c4x) && (c1y < c3y) && (c2y > c4y))
			return true;
		return false;
	}
}
