#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const double pi = 4 * atan(1);
const double Pi = 4 * atan(1);

// namespace Geo2D
// {

    const double pi = acos(-1.0);
    const double eps = 1e-9;
    double ang;
    typedef double T;

    struct pt
    {
        T x, y;
        pt() {}
        pt(T _x, T _y) : x(_x), y(_y) {}
        pt operator+(const pt &p) const
        {
            return pt(x + p.x, y + p.y);
        }
        pt operator-(const pt &p) const
        {
            return pt(x - p.x, y - p.y);
        }
        pt operator*(const T &d) const
        {
            return pt(x * d, y * d);
        }
        pt operator/(const T &d) const
        {
            return pt(x / d, y / d);
        }
        bool operator==(const pt &p) const
        {
            return (x == p.x and y == p.y);
        }
        bool operator!=(const pt &p) const
        {
            return !(x == p.x and y == p.y);
        }
        bool operator<(const pt &p) const
        {
            if (x != p.x)
                return x < p.x;
            return y < p.y;
        }
    };

    T sq(pt p)
    {
        return p.x * p.x + p.y * p.y;
    }

    double abs(pt p)
    {
        return sqrt(sq(p));
    }

    pt translate(pt v, pt p)
    {
        return p + v;
    }

    pt scale(pt c, double factor, pt p)
    {
        return c + (p - c) * factor;
    }

    pt rot(pt p, double a)
    {
        return pt(p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a));
    }

    pt perp(pt p)
    {
        return pt(-p.y, p.x);
    }

    T dot(pt v, pt w)
    {
        return v.x * w.x + v.y * w.y;
    }

    bool isPerp(pt v, pt w)
    {
        return dot(v, w) == 0;
    }

    double smallAngle(pt v, pt w)
    {
        double cosTheta = dot(v, w) / abs(v) / abs(w);
        if (cosTheta < -1)
            cosTheta = -1;
        if (cosTheta > 1)
            cosTheta = 1;
        return acos(cosTheta);
    }

    T cross(pt v, pt w)
    {
        return v.x * w.y - v.y * w.x;
    }

    T orient(pt a, pt b, pt c)
    {
        return cross(b - a, c - a);
    }

    bool inAngle(pt a, pt b, pt c, pt x)
    {
        assert(orient(a, b, c) != 0);
        if (orient(a, b, c) < 0)
            swap(b, c);
        return orient(a, b, x) >= 0 and orient(a, c, x) <= 0;
    }

    //Line
    struct line
    {
        pt v;
        T c;
        line() {}
        //From points P and Q
        line(pt p, pt q)
        {
            v = (q - p);
            c = cross(v, p);
        }
        //From equation ax + by = c
        line(T a, T b, T c)
        {
            v = pt(b, -a);
            c = c;
        }
        //From direction vector v and offset c
        line(pt v, T c)
        {
            v = v;
            c = c;
        }

        //These work with T = int / double
        double side(pt p);
        double dist(pt p);
        double sqDist(pt p);
        line perpThrough(pt p);
        bool cmpProj(pt p, pt q);
        line translate(pt t);

        //These require T = double
        line shiftLeft(double dist);
        pt proj(pt p);
        pt refl(pt p);
    };

    double line ::side(pt p)
    {
        return cross(v, p) - c;
    }

    double line ::dist(pt p)
    {
        return abs(side(p)) / abs(v);
    }
    double line ::sqDist(pt p)
    {
        return side(p) * side(p) / (double)sq(v);
    }

    line line ::perpThrough(pt p)
    {
        return line(p, p + perp(v));
    }

    bool line ::cmpProj(pt p, pt q)
    {
        return dot(v, p) < dot(v, q);
    }

    line line ::translate(pt t)
    {
        return line(v, c + cross(v, t));
    }

    line line ::shiftLeft(double dist)
    {
        return line(v, c + dist * abs(v));
    }

    bool areParallel(line l1, line l2)
    {
        return (l1.v.x * l2.v.y == l1.v.y * l2.v.x);
    }

    bool areSame(line l1, line l2)
    {
        return areParallel(l1, l2) and (l1.v.x * l2.c == l2.v.x * l1.c) and (l1.v.y * l2.c == l2.v.y * l1.c);
    }

    bool inter(line l1, line l2, pt &out)
    {
        T d = cross(l1.v, l2.v);
        if (d == 0)
            return false;
        out = (l2.v * l1.c - l1.v * l2.c) / d;
        return true;
    }

    pt line ::proj(pt p)
    {
        return p - perp(v) * side(p) / sq(v);
    }

    pt line ::refl(pt p)
    {
        return p - perp(v) * 2 * side(p) / sq(v);
    }

    line intBisector(line l1, line l2, bool interior)
    {
        assert(cross(l1.v, l2.v) != 0);
        double sign = interior ? 1 : -1;
        return line(l2.v / abs(l2.v) + l1.v * sign / abs(l1.v),
                    l2.c / abs(l2.v) + l1.c * sign / abs(l1.v));
    }

    //Segment
    bool inDisk(pt a, pt b, pt p)
    {
        return dot(a - p, b - p) <= 0;
    }

    bool onSegment(pt a, pt b, pt p)
    {
        return orient(a, b, p) == 0 and inDisk(a, b, p);
    }

    bool properInter(pt a, pt b, pt c, pt d, pt &i)
    {
        double oa = orient(c, d, a),
               ob = orient(c, d, b),
               oc = orient(a, b, c),
               od = orient(a, b, d);

        //Proper intersection exists iff opposite signs
        if (oa * ob < 0 and oc * od < 0)
        {
            i = (a * ob - b * oa) / (ob - oa);
            return true;
        }
        return false;
    }

    bool inters(pt a, pt b, pt c, pt d)
    {
        pt out;
        if (properInter(a, b, c, d, out))
            return true;
        if (onSegment(c, d, a))
            return true;
        if (onSegment(c, d, b))
            return true;
        if (onSegment(a, b, c))
            return true;
        if (onSegment(a, b, d))
            return true;
        return false;
    }

    double segPoint(pt a, pt b, pt p)
    {
        if (a != b)
        {
            line l(a, b);
            if (l.cmpProj(a, p) and l.cmpProj(p, b))
                return l.dist(p);
        }
        return min(abs(p - a), abs(p - b));
    }

    double segSeg(pt a, pt b, pt c, pt d)
    {
        pt dummy;
        if (properInter(a, b, c, d, dummy))
            return 0;
        return min(min(min(segPoint(a, b, c), segPoint(a, b, d)), segPoint(c, d, a)), segPoint(c, d, b));
    }

    //int latticePoints (pt a, pt b){
    //    //requires int representation
    //    return __gcd (abs (a.x - b.x), abs (a.y - b.y)) + 1;
    //}

    bool isConvex(vector<pt> &p)
    {
        bool hasPos = false, hasNeg = false;
        for (int i = 0, n = p.size(); i < n; i++)
        {
            int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
            if (o > 0)
                hasPos = true;
            if (o < 0)
                hasNeg = true;
        }
        return !(hasPos and hasNeg);
    }

    double areaTriangle(pt a, pt b, pt c)
    {
        return abs(cross(b - a, c - a)) / 2.0;
    }

    double areaPolygon(const vector<pt> &p)
    {
        double area = 0.0;
        for (int i = 0, n = p.size(); i < n; i++)
        {
            area += cross(p[i], p[(i + 1) % n]);
        }
        return fabs(area) / 2.0;
    }

    ll is_point_in_convex(vector<pt> &p, pt &x) // O(log n)
    {
        ll n = p.size();
        if (n < 3)
            return 1;
        ll a = orient(p[0], p[1], x), b = orient(p[0], p[n - 1], x);
        if (a < 0 || b > 0)
            return 1;
        ll l = 1, r = n - 1;
        while (l + 1 < r)
        {
            int mid = l + r >> 1;
            if (orient(p[0], p[mid], x) >= 0)
                l = mid;
            else
                r = mid;
        }
        ll k = orient(p[l], p[r], x);
        if (k <= 0)
            return -k;
        if (l == 1 && a == 0)
            return 0;
        if (r == n - 1 && b == 0)
            return 0;
        return -1;
    }

    bool pointInPolygon(const vector<pt> &p, pt q) //rezaul vai's
    {
        bool c = false;
        for (int i = 0, n = p.size(); i < n; i++)
        {
            int j = (i + 1) % p.size();
            if ((p[i].y <= q.y and q.y < p[j].y or p[j].y <= q.y and q.y < p[i].y) and
                q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
                c = !c;
        }
        return c;
    }

    pt centroidPolygon(const vector<pt> &p)
    {
        pt c(0, 0);
        double scale = 6.0 * areaPolygon(p);
        //    if (scale < eps) return c;
        for (int i = 0, n = p.size(); i < n; i++)
        {
            int j = (i + 1) % n;
            c = c + (p[i] + p[j]) * cross(p[i], p[j]);
        }
        return c / scale;
    }

    //Circle
    pt circumCenter(pt a, pt b, pt c)
    {
        b = b - a;
        c = c - a;
        assert(cross(b, c) != 0);
        return a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2;
    }

    bool circle2PtsRad(pt p1, pt p2, double r, pt &c)
    {
        double d2 = sq(p1 - p2);
        double det = r * r / d2 - 0.25;
        if (det < 0.0)
            return false;
        double h = sqrt(det);
        c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
        c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
        return true;
    }

    int circleLine(pt c, double r, line l, pair<pt, pt> &out)
    {
        double h2 = r * r - l.sqDist(c);
        if (h2 < 0)
            return 0; // the line doesn't touch the circle;
        pt p = l.proj(c);
        pt h = l.v * sqrt(h2) / abs(l.v);
        out = make_pair(p - h, p + h);
        return 1 + (h2 > 0);
    }

    int circleCircle(pt c1, double r1, pt c2, double r2, pair<pt, pt> &out)
    {
        pt d = c2 - c1;
        double d2 = sq(d);
        if (d2 == 0)
        { //concentric circles
            assert(r1 != r2);
            return 0;
        }
        double pd = (d2 + r1 * r1 - r2 * r2) / 2;
        double h2 = r1 * r1 - pd * pd / d2; // h ^ 2
        if (h2 < 0)
            return 0;
        pt p = c1 + d * pd / d2, h = perp(d) * sqrt(h2 / d2);
        out = make_pair(p - h, p + h);
        return 1 + h2 > 0;
    }

    int tangents(pt c1, double r1, pt c2, double r2, bool inner, vector<pair<pt, pt>> &out)
    {
        if (inner)
            r2 = -r2;
        pt d = c2 - c1;
        double dr = r1 - r2, d2 = sq(d), h2 = d2 - dr * dr;
        if (d2 == 0 or h2 < 0)
        {
            assert(h2 != 0);
            return 0;
        }
        for (int sign : {-1, 1})
        {
            pt v = pt(d * dr + perp(d) * sqrt(h2) * sign) / d2;
            out.push_back(make_pair(c1 + v * r1, c2 + v * r2));
        }
        return 1 + (h2 > 0);
    }

    //Convex Hull - Monotone Chain
    int sz; //returned polygon's size;
    pt H[100000 + 5];
    vector<pt> monotoneChain(vector<pt> &v) /// from you_know_who
    {
        if (v.size() == 1)
            return v;

        sort(v.begin(), v.end());
        vector<pt> up(2 * v.size() + 2), down(2 * v.size() + 2);
        int szup = 0, szdw = 0;

        for (int i = 0; i < v.size(); i++)
        {
            // cout<<"p: ("<<v[i].x<<" "<<v[i].y<<" )"<<endl;
            while (szup > 1 && orient(up[szup - 2], up[szup - 1], v[i]) >= 0)
                szup--;
            while (szdw > 1 && orient(down[szdw - 2], down[szdw - 1], v[i]) <= 0)
                szdw--;
            up[szup++] = v[i];
            down[szdw++] = v[i];
        }

        if (szdw > 1)
            szdw--;

        reverse(up.begin(), up.begin() + szup);
        for (int i = 0; i < szup - 1; i++)
            down[szdw++] = up[i];

        if (szdw == 2 && down[0].x == down[1].x && down[0].y == down[1].y)
        {
            szdw--;
        }
        sz = szdw;

        return down;
    }

    pt toPoint(pt p1, pt p2)
    {
        return pt(p2.x - p1.x, p2.y - p1.y);
    }

    double angle(pt a, pt o, pt b)
    {
        //double result = atan2(P3.y - P1.y, P3.x - P1.x) - atan2(P2.y - P1.y, P2.x - P1.x);

        double result;

        pt oa = toPoint(o, a);
        pt ob = toPoint(o, b);

        if (sq(oa) == 0 || sq(ob) == 0)
        {
            return 0.0;
        }

        result = acos(dot(oa, ob) / sqrt(sq(oa) * sq(ob)));
        result *= 180.0;
        result /= Pi;
        return result;
    }
// }
// using namespace Geo2D;

namespace Geo3D
{
    const double eps = 1e-10;
    inline int dcmp(double x)
    {
        if (fabs(x) < eps)
            return 0;
        else
            return x < 0 ? -1 : 1;
    }
    inline double torad(double deg) { return deg / 180 * pi; }

    struct Point
    {
        double x, y;
        Point(double x = 0, double y = 0) : x(x), y(y) {}

        Point operator+(const Point &u) { return Point(x + u.x, y + u.y); }
        Point operator-(const Point &u) { return Point(x - u.x, y - u.y); }
        Point operator*(const double u) { return Point(x * u, y * u); }
        Point operator/(const double u) { return Point(x / u, y / u); }
        double operator*(const Point &u) { return x * u.y - y * u.x; }
    };

    struct Point3D
    {
        double x, y, z;
        Point3D() {}
        void read() { cin >> x >> y >> z; }
        void write() { cout << x << " --- " << y << " --- " << z << "\n"; }

        Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
        Point3D(const Point3D &p) : x(p.x), y(p.y), z(p.z) {}
        Point3D operator+(Point3D b) { return Point3D(x + b.x, y + b.y, z + b.z); }
        Point3D operator-(Point3D b) { return Point3D(x - b.x, y - b.y, z - b.z); }
        Point3D operator*(double b) { return Point3D(x * b, y * b, z * b); }
        Point3D operator/(double b) { return Point3D(x / b, y / b, z / b); }
        bool operator<(Point3D b) { return make_pair(make_pair(x, y), z) < make_pair(make_pair(b.x, b.y), b.z); }
        bool operator==(Point3D b) { return dcmp(x - b.x) == 0 && dcmp(y - b.y) == 0 && dcmp(z - b.z) == 0; }
    };
    typedef Point3D Vector3D;
    typedef vector<Point> Polygon;
    typedef vector<Point3D> Polyhedron;

    namespace Vectorial
    {
        double getDot(Vector3D a, Vector3D b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
        Vector3D getCross(Vector3D a, Vector3D b) { return Point3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
        double getLength(Vector3D a) { return sqrt(getDot(a, a)); }
        double getPLength(Vector3D a) { return getDot(a, a); }
        Vector3D unitVector(Vector3D v) { return v / getLength(v); }

        double getUnsignedAngle(Vector3D u, Vector3D v)
        {
            double cosTheta = getDot(u, v) / getLength(u) / getLength(v);
            cosTheta = max(-1.0, min(1.0, cosTheta));
            return acos(cosTheta);
        }

        Vector3D rotate(Vector3D v, Vector3D a, double rad)
        {
            a = unitVector(a);
            return v * cos(rad) + a * (1 - cos(rad)) * getDot(a, v) + getCross(a, v) * sin(rad);
        }
    }

    using namespace Vectorial;
};

using namespace Geo3D;
