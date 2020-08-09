#include<iostream>
#include<string>
#include<vector>
#include<Eigen/Core>
#include<Eigen/Geometry>
using namespace std;


class Shape
{
private:
    string name_; // 具体是哪个shape:"circle","rect","tri"
    vector<Eigen::Vector2d> points_;
    Eigen::Vector2d center_;

public:
    Shape(vector<Eigen::Vector2d> points, string name) : name_(name), points_(points) {};
    ~Shape() {};
    string getName() {return name_;}
    vector<Eigen::Vector2d> getPoints() {return points;}
    void ComputeCenter() { //计算一下质心，赋给center_}

}


bool MoveShape(vector<Shape> &shapes, double x, double y, double r, vector<Shape>& outShapes)
{
    Eigen::Matrix3d T;//得到3x3的变换矩阵
    if (shapes.empty()) return false;
    for(auto shape : shapes)
    {
        for(auto point : shape.getPoints)
        {
            // 先扩维，把点扩成3x1，再乘以变换矩阵，然后注意是绕质心的旋转
        }
    }
}