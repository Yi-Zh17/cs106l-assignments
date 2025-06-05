class Rectangle {
public:
    // Custom constructor
    Rectangle(double width, double height);
    // Default constuctor
    Rectangle();

    // Getter function
    double getWidth() const;
    double getHeight() const;
    double getSize() const;

    // Setter function
    void setWidth(double newWidth);
    void setHeight(double NewHeight);
    void updateSize();

private:
    // Private fields
    double width;
    double height;
    double size;
    // Private member function
    double calcSize(double width, double height);
};
