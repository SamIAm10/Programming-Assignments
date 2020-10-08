
public interface Rectangle {
	
      /**
      * Returns the X coordinate of the center of the framing rectangle of the Shape in double precision.
      *
      * @return the X coordinate of the center of the framing rectangle of the Shape.
      */
      public double getCenterX();
      
      /**
      * Returns the Y coordinate of the center of the framing rectangle of the Shape in double precision.
      *
      * @return the Y coordinate of the center of the framing rectangle of the Shape.
      */
      public double getCenterY();
      
      /**
      * Returns the width of the bounding Rectangle in double precision.
      *
      * @return the width of the bounding Rectangle.
      */
      public double getWidth();
       
      /**
      * Returns the height of the bounding Rectangle in double precision.
      *
      * @return the height of the bounding Rectangle.
      */
      public double getHeight();
       
      /**
      * Set X-Coordinate of the center point of the rectangle.
      *
      * @param cx X-Coordinate in double precision
      * @return no return value
      */
      public void setCenterX(double cx);

      /**
      * Set Y-Coordinate of the center point of the rectangle.
      *
      * @param cy Y-Coordinate in double precision
      * @return no return value
      */
      public void setCenterY(double cy);
       
      /**
      * Set width of the rectangle
      *
      * @param w Width in double precision
      * @return no return value
      */
      public void setWidth(double w);
       
      /**
      * Set height of the rectangle
      *
      * @param h Height in double precision
      * @return no return value
      */
      public void setHeight(double h);
       
      /**
      * Get parameter of the rectangle
      *
      * @return Parameter of rectangle in double precision
      */
      public double getPerimeter();
       
      /**
      * Check whether this rectangle intersects Rectangle r or not
      *
      * @param r Rectangle to be checked
      * @return Boolean value true or false
      */
      public boolean intersects(Rectangle r);
       
      /**
      * Check whether this rectangle contains Rectangle r or not
      *
      * @param r Rectangle to be checked
      * @return Boolean value true or false
      */
      public boolean contains(Rectangle r);
}