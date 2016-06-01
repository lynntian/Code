class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {

        long area = 0; //check
        if( A > C || B >D || E >G || H < F) return area;

        area = (C-A) * (D-B) + (G-E) * (H-F);
        cout << "area: " << area<<endl;
        long x = 0; long y = 0;
        if(findOverlapping(A,C, E,G, x) && findOverlapping(B,D, F, H, y))
        {
            area -= abs(x) * abs(y);
        }
        return area;
    }

    bool findOverlapping(int p1f, int p1s, int p2f, int p2s, long& resf)
    {
        if(p1f >= p2s || p1s <= p2f) return false;
        resf = ((p1s <= p2s) ? p1s:p2s) - ((p1f >= p2f) ? p1f : p2f);
        cout << "resf: " << resf << endl;
        return true;
    }
};

//class Solution {public: int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) { int l = min(max(A, E), C); int r = min(max(A, G), C); int t = min(max(B, H), D); int b = min(max(B, F), D); return (C-A)*(D-B) + (G-E)*(H-F) - (r-l)*(t-b); } };