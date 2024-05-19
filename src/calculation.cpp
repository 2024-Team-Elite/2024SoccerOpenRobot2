#include <calculation.h>

Calculation::Calculation()
{
}
int Calculation::projectionCalc(int anglebisc, int robotAngle)
{
    int lineAngle = anglebisc + 180;
    if (lineAngle > 360)
    {
        lineAngle = lineAngle - 360;
    }
    int angleDiff = abs(robotAngle-lineAngle);
    if (angleDiff > 180)
    {
        angleDiff = 360 - angleDiff;
    }
    if(angleDiff > 90){
        return robotAngle;
    }
    lineAngle = anglebisc + 90;
    if (lineAngle > 360)
    {
        lineAngle = lineAngle - 360;
    }
    vectorX = getX(lineAngle);
    vectorY = getY(lineAngle);
    robotAngleX = getX(robotAngle);
    robotAngleY = getY(robotAngle);
    dotProduct = (robotAngleX * vectorX) + (robotAngleY * vectorY);
    denominator = pow(vectorX, 2) + pow(vectorY, 2);
    robotAngleX = (dotProduct / denominator) * vectorX;
    robotAngleY = (dotProduct / denominator) * vectorY;

    return getAngle(robotAngleX, robotAngleY);
}
double Calculation::getAngle(double x, double y)
{
    double angle = toDegrees(atan2(x, y));
    if (angle < 0)
    {
        angle = angle + 360;
    }
    return angle;
}
double Calculation::getX(int angle)
{
    return sin(toRadians(angle));
}
double Calculation::getY(int angle)
{
    return cos(toRadians(angle));
}
int Calculation::complimentaryFilter(int angle, int prevAngle)
{
    angleDiff = abs(angle - prevAngle);
    if(angleDiff >= 180){
        angleDiff = 360-angleDiff;
        if(angle > prevAngle)
            angle = prevAngle - angleDiff;
        else
            angle = prevAngle + angleDiff;
    }

    int weightedValue = ((0.95 * angle) + (0.05 * prevAngle));
    if(weightedValue >= 360)
        weightedValue -= 360;
    if(weightedValue < 0){
        weightedValue += 360;
    }
    return weightedValue;
}