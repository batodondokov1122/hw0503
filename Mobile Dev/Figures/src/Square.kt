// TODO: дополнить определение класса размерами и позицией
class Square(var x: Int, var y: Int, var a: Int) :Figure(0), Transforming  {
    // TODO: унаследовать от Figure, реализовать area()
    // TODO: реализовать интерфейс Transforming

    override fun area(): Float {
        return (a*a).toFloat()
    }

    override fun resize(zoom: Int) {
        a *= zoom
    }

    override fun rotate(direction: RotateDirection, centerX: Int, centerY: Int) {
        var newX = 0
        var newY = 0
        if (direction == RotateDirection.Clockwise){
            newX = centerX + (y - centerY)
            newY = centerY - (x - centerX)
        }else{
            newX = centerX - (y - centerY)
            newY = centerY + (x - centerX)
        }
        x = newX
        y = newY
    }

    override fun figureToString(): String {
        return "Square x = $x, y = $y, a = $a"
    }
}