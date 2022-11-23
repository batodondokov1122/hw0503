// TODO: дополнить определение класса размерами и позицией
class Circle (var x: Int, var y: Int, var r:Int): Figure(0), Transforming {
    // TODO: реализовать интерфейс Transforming
    override fun area(): Float {
        return  (r * r * Math.PI).toFloat();
    }

    override fun resize(zoom: Int) {
        r *= zoom
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
        return "Circle x = $x, y = $y, r = $r"
    }
}