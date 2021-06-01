#include "Triangle.h";

bool Triangle::intersect(Vector3D& originray, Vector3D& directionray, intersectParameters& param, float& t0, float& t1) const
{
    Vector3D edge1 = b - a;
    Vector3D edge2 = c - a;
    Vector3D h = directionray.crossprod(edge2);
    auto dotprod_a = edge1.dot(h);

    if (dotprod_a > -kEpsilon && dotprod_a < kEpsilon)
    {
        return false;
    }
    float f = 1 / dotprod_a;
    Vector3D s = originray - a;
    float u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
    {
        return false;
    }
    Vector3D q = s.crossprod(edge1);
    float v = f * directionray.dot(q);
    if (v < 0.0 || ((double)u + (double)v) > 1.0)
    {
        return false;
    }

    float t = f * edge2.dot(q);
    t0 = t;
    t1 = t;
    param = intersectParameters(
        t,
        (originray + directionray * t),
        getnormal(Vector3D(u, v, 0))
    );
    return true;
}
Triangle& Triangle::operator +(Vector3D v) {
    a += v;
    b += v;
    c += v;
    return *this;
}
void Triangle::setDotNormals(Vector3D norm1, Vector3D norm2, Vector3D norm3) {
    a_norm = norm1;
    b_norm = norm2;
    c_norm = norm3;
    dotNormals = true;

}
Vector3D Triangle::getnormal(Vector3D uv) const {
    if (dotNormals) {
        return a_norm * (1 - uv.x - uv.y) + b_norm * uv.x + c_norm * uv.y;
    }
    else {
        return normal;
    }
};
float Triangle::getMedianByAxis(axis axis) {
    switch (axis)
    {
    case axis::X:
        return this->median.x;
        break;
    case axis::Y:
        return this->median.y;
        break;
    case axis::Z:
        return this->median.z;
        break;
    }
};

void Triangle::transform(MatrixTRS m) {
    a = m.mult(a);

    //std::cout << a.x << " " << a.y << " " << a.z << std::endl;
    b = m.mult(b);
    //std::cout << b.x << " " << b.y << " " << b.z << std::endl;
    c = m.mult(c);
    //std::cout << c.x << " " << c.y << " " << c.z << std::endl;
    if (dotNormals) {
        a_norm = m.torotate(a_norm);

        b_norm = m.torotate(b_norm);

        c_norm = m.torotate(c_norm);
    }
    normal = (b - a).crossprod(c - a);
}