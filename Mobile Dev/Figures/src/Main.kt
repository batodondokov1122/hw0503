fun main() {
    val circle1 = Circle(4,3, 3)
    println(circle1.figureToString())
    circle1.resize(2)
    circle1.rotate(RotateDirection.CounterClockwise, 3, -3)
    println(circle1.figureToString())

    val rect1 = Rect(-1,2, 2,3)
    println(rect1.figureToString())
    rect1.resize(2)
    rect1.rotate(RotateDirection.Clockwise, -3, -5)
    println(rect1.figureToString())

    val square1 = Square(0,0, 1)
    println(square1.figureToString())
    square1.resize(4)
    square1.rotate(RotateDirection.Clockwise, -3, -5)
    square1.rotate(RotateDirection.Clockwise, -3, -5)
    square1.rotate(RotateDirection.Clockwise, -3, -5)
    square1.rotate(RotateDirection.Clockwise, -3, -5)
    println(square1.figureToString())
}


