#include <iostream>
#include <limits.h>
#include <vector>
#include <cmath>
using namespace std;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class Solution {
    public:
        vector<Point> convex_hull;

        // https://en.wikipedia.org/wiki/Quickhull
        // 然而漏掉了某些点
        // so we add online vector
        // and changed right to (right or online) in FindHull;
        vector<Point> outerTrees(vector<Point>& points) {
            // Convex Hull := {} 
            convex_hull.resize(0);

            if (points.size() == 1) {
                return points;
            }

            // Find left and right most points, say A & B, and add A & B to convex hull 
            Point    A;
            Point    B;
            int      min = 1000;
            int      max = -1;
            for (auto p : points) {
                if (p.x > max) {
                    max = p.x;
                    B.x = p.x;
                    B.y = p.y;
                }
                if (p.x < min) {
                    min = p.x;
                    A.x = p.x;
                    A.y = p.y;
                }
            }
            convex_hull.push_back(A);
            convex_hull.push_back(B);
            cout << "pushing back 2: x : " << A.x  << " y: " << A.y << endl;
            cout << "pushing back 2: x : " << B.x  << " y: " << B.y << endl;

            // Segment AB divides the remaining (n-2) points into 2 groups S1 and S2 
            //   where S1 are points in S that are on the right side of the oriented line from A to B, 
            //   and S2 are points in S that are on the right side of the oriented line from B to A 
            vector<Point> S1;
            vector<Point> S2;
            vector<Point> online;
            // http://blog.sina.com.cn/s/blog_4dbb5c5f0101fxzn.html
            int a   = B.y - A.y;
            int b   = A.x - B.x;
            int c   = B.x * A.y - A.x * B.y;

            for (auto p : points) {
                if (p.x == A.x && p.y == A.y) {
                    continue;
                }
                if (p.x == B.x && p.y == B.y) {
                    continue;
                }
                int d = a * p.x + b * p.y + c;
                if (d > 0) {
                    // A->B 's right 
                    S1.push_back(p);
                } else if (d < 0) {
                    // B->A 's right 
                    S2.push_back(p);
                } else {
                    // on the line
                    online.push_back(p);
                }
            }

            cout << "S1" << endl;
            printVector(S1);
            cout << "S2" << endl;
            printVector(S2);

            if (S1.size() == 0 || S2.size() == 0) {
                for (auto p : online) {
                    convex_hull.push_back(p);
                    cout << "pushing back online: x : " << p.x  << " y: " << p.y << endl;
                }
            }
            // FindHull (S1, A, B) 
            FindHull(S1, A, B);
            // FindHull (S2, B, A) 
            FindHull(S2, B, A);

            return convex_hull;
        }

        // Find points on convex hull from the set Sk of points 
        // that are on the right side of the oriented line from P to Q
        void FindHull (vector<Point> &Sk, Point &P, Point &Q) {
            // If Sk has no point, then return. 
            if (Sk.size() == 0) {
                return;
            }

            // From the given set of points in Sk, find farthest point, say C, from segment PQ 
            Point   C;

            int aaa = Q.y - P.y;
            int bbb = P.x - Q.x;
            int ccc = Q.x * P.y - P.x * Q.y;

            double max = -1;
            for (auto p : Sk) {
                double dis;
                // dist(line: ax+by+c=0, and point(x0, y0)): (a*x0 + b*y0 + c)/sqrt(a^2+b^2)

                dis = fabs(aaa * p.x + bbb * p.y + ccc) / sqrt(aaa * aaa + bbb * bbb);
                if (dis > max) {
                    max = dis;
                    C.x = p.x;
                    C.y = p.y;
                }
            }
            //     Add point C to convex hull at the location between P and Q 
            convex_hull.push_back(C);
            cout << "pushing back 1: x : " << C.x  << " y: " << C.y << endl;

            //     Three points P, Q, and C partition the remaining points of Sk into 3 subsets: S0, S1, and S2 
            //     where S0 are points inside triangle PCQ, S1 are points on the right side of the oriented 
            //     line from  P to C, and S2 are points on the right side of the oriented line from C to Q. 
            vector<Point> S1;
            vector<Point> S2;
            int a   = C.y - P.y;
            int b   = P.x - C.x;
            int c   = C.x * P.y - P.x * C.y;

            int aa   = Q.y - C.y;
            int bb   = C.x - Q.x;
            int cc   = Q.x * C.y - C.x * Q.y;
            for (auto p : Sk) {
                if (p.x == C.x && p.y == C.y) {
                    continue;
                }
                int d = a * p.x + b * p.y + c;
                if (d >= 0) {
                    // right or on the line
                    S1.push_back(p);
                    continue;
                }
                int dd = aa * p.x + bb * p.y + cc;
                if (dd >= 0) {
                    S2.push_back(p);
                    continue;
                }
            }
            //     FindHull(S1, P, C) 
            FindHull(S1, P, C);
            //     FindHull(S2, C, Q) 
            FindHull(S2, C, Q);
        }

        void printVector(vector<Point> points) {
            for (auto p : points) {
                cout << p.x << ":" << p.y << endl;
            }
        }
};

int main() {
    Solution * o = new Solution();

    {
        vector<Point> all_points;
        Point p(0,0);
        (all_points).push_back(p);
        p.x = 0; p.y = 1;
        (all_points).push_back(p);
        p.x = 0; p.y = 2;
        (all_points).push_back(p);
        p.x = 1; p.y = 2;
        (all_points).push_back(p);
        p.x = 2; p.y = 2;
        (all_points).push_back(p);
        p.x = 3; p.y = 2;
        (all_points).push_back(p);
        p.x = 3; p.y = 1;
        (all_points).push_back(p);
        p.x = 3; p.y = 0;
        (all_points).push_back(p);
        p.x = 2; p.y = 0;
        (all_points).push_back(p);
        p.x = 1; p.y = 0;
        (all_points).push_back(p);
        p.x = 1; p.y = 1;
        (all_points).push_back(p);
        p.x = 3; p.y = 3;
        (all_points).push_back(p);

        cout << "all points" << endl;
        o->printVector(all_points);

        vector<Point> points    = o->outerTrees(all_points);
        cout << "convex_hull" << endl;
        o->printVector(points);
    }
    return 0;

    cout << "======================" << endl;

    {
        vector<Point> all_points;
        Point a(1, 2);
        Point b(2, 2);
        Point c(4, 2);
        Point d(5, 2);
        (all_points).push_back(a);
        (all_points).push_back(b);
        (all_points).push_back(c);
        (all_points).push_back(d);

        cout << "all points" << endl;
        o->printVector(all_points);

        vector<Point> points    = o->outerTrees(all_points);
        cout << "convex_hull" << endl;
        o->printVector(points);
    }

    cout << "======================" << endl;

    {
        vector<Point> all_points;
        Point a(1, 1);
        Point b(2, 2);
        Point c(2, 0);
        Point d(2, 4);
        Point e(3, 3);
        Point f(4, 2);
        (all_points).push_back(a);
        (all_points).push_back(b);
        (all_points).push_back(c);
        (all_points).push_back(d);
        (all_points).push_back(e);
        (all_points).push_back(f);

        cout << "all points" << endl;
        o->printVector(all_points);

        vector<Point> points    = o->outerTrees(all_points);
        cout << "convex_hull" << endl;
        o->printVector(points);
    }

    return 0;
}
