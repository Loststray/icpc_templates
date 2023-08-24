#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
class BigInteger
{
public:
    BigInteger() = default;
    BigInteger(const string &s)
    {
        int n = s.size(), minIdx = 0;
        if (s[0] == '-')
            isPositive = false, minIdx = 1;
        else if (s[0] == '+')
            isPositive = true, minIdx = 1;
        for (int i = n - 1; i >= minIdx; i -= digit)
        {
            int beg = max(minIdx, i - digit + 1);
            nums.push_back(stoi(s.substr(beg, i - beg + 1)));
        }
        cutLeadZero();
    }
    BigInteger(ll a) : BigInteger(to_string(a)) {}
    BigInteger(const BigInteger &bInt) : nums(bInt.nums), isPositive(bInt.isPositive), length(bInt.length) {}
    BigInteger(BigInteger &&bInt) noexcept : nums(move(bInt.nums)), isPositive(bInt.isPositive), length(bInt.length) {}
    BigInteger(const vector<int> &vec, bool sign = true) : nums(vec), isPositive(sign) { cutLeadZero(); }

    friend istream &operator>>(istream &is, BigInteger &bInt)
    {
        string s;
        is >> s;
        bInt = move(BigInteger(s));
        return is;
    }
    friend ostream &operator<<(ostream &os, const BigInteger &bInt)
    {
        os << (string)bInt;
        return os;
    }
    operator string() const
    {
        string ans;
        if (!isPositive)
            ans += "-";
        int n = nums.size();
        for (int i = n - 1; i >= 0; i--)
        {
            string s = to_string(nums[i]);
            if (i != n - 1)
                ans += string(digit - s.size(), '0');
            ans += s;
        }
        return ans;
    }
    // һԪ����
    const BigInteger &operator+() const { return *this; }
    // һԪ����
    BigInteger operator-() const
    {
        BigInteger tmp(*this);
        if (!tmp.isZero())
            tmp.isPositive = !isPositive;
        return tmp;
    }
    // �Ƚ������
    bool operator<(const BigInteger &bInt) const
    {
        if (isPositive && !bInt.isPositive)
            return false;
        if (!isPositive && bInt.isPositive)
            return true;
        bool flag = true;
        if (!isPositive)
            flag = false; // ��Ϊ����
        if (length < bInt.length)
            return flag;
        else if (length > bInt.length)
            return !flag;
        int n = size();
        for (int i = n - 1; i >= 0; i--)
        {
            if (nums[i] < bInt[i])
                return flag;
            else if (nums[i] > bInt[i])
                return !flag;
        }
        return false;
    }
    bool operator<=(const BigInteger &bInt) const
    {
        if (isPositive && !bInt.isPositive)
            return false;
        if (!isPositive && bInt.isPositive)
            return true;
        bool flag = true;
        if (!isPositive)
            flag = false; // ��Ϊ����
        if (length < bInt.length)
            return flag;
        else if (length > bInt.length)
            return !flag;
        int n = size();
        for (int i = n - 1; i >= 0; i--)
        {
            if (nums[i] < bInt[i])
                return flag;
            else if (nums[i] > bInt[i])
                return !flag;
        }
        return true;
    }
    bool operator==(const BigInteger &bInt) const
    {
        if (length != bInt.length)
            return false;
        int n = size();
        for (int i = 0; i < n; i++)
            if (nums[i] != bInt[i])
                return false;
        return true;
    }
    // ���������
    BigInteger operator+(const BigInteger &bInt) const
    {
        if (!bInt.isPositive)
            return *this - (-bInt); // ���ϸ��� = ��ȥ�����ֵ
        if (!isPositive)
            return bInt - (-*this); // ����+���� = ����-(-����)
        // Ҫô���� Ҫô����
        vector<int> ans;
        int n = size(), m = bInt.size(), sum = 0, i = 0, j = 0;
        while (i < n || j < m || sum)
        {
            if (i < n)
                sum += nums[i++];
            if (j < m)
                sum += bInt[j++];
            ans.push_back(sum % mod);
            sum /= mod;
        }
        return move(BigInteger(ans, isPositive));
    }
    BigInteger operator-(const BigInteger &bInt) const
    {
        if (!bInt.isPositive)
            return *this + (-bInt); // ��ȥ���� = ���������ֵ
        if (!isPositive)
            return -((-*this) + bInt); // ����-���� = -(-���� + ����)
        if (*this < bInt)
            return -(bInt - *this);
        // ֻ���������ȥС��
        vector<int> ans;
        int i = 0, j = 0, n = size(), m = bInt.size(), sum = 0;
        while (i < n || j < m || sum)
        {
            if (i < n)
                sum += nums[i++];
            if (j < m)
                sum -= bInt[j++];
            int flag = 0;
            if (sum < 0)
            {
                flag = -1;
                sum += mod;
            }
            ans.push_back(sum);
            sum = flag;
        }
        return move(BigInteger(ans));
    }
    BigInteger operator*(const BigInteger &bInt) const
    {
        int n = size(), m = bInt.size();
        vector<int> ans(n + m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                ll tmp = ans[i + j] + nums[i] * 1ll * bInt[j];
                ans[i + j] = tmp % mod;
                ans[i + j + 1] += tmp / mod;
            }
        }
        return move(BigInteger(ans, isPositive == bInt.isPositive));
    }
    // �����᷵�� �̺�����
    pair<BigInteger, BigInteger> operator/(const BigInteger &bInt) const
    {
        BigInteger a = abs();
        BigInteger b = bInt.abs();
        if (b.isZero())
            return pair<BigInteger, BigInteger>(*this, move(b));
        if (a < b)
            return pair<BigInteger, BigInteger>(move(BigInteger(0)), *this);
        int len = a.length - b.length + 1;
        string ans;
        if (isPositive != bInt.isPositive)
            ans = "-";
        for (int i = 0; i < len; i++)
        {
            BigInteger tmp = e(len - i - 1) * b;
            int times = 0;
            while (tmp <= a)
            {
                a = a - tmp;
                ++times;
            }
            ans += to_string(times + '0');
        }
        a.isPositive = isPositive;
        return pair<BigInteger, BigInteger>(move(BigInteger(ans)), move(a));
    }
    int operator[](int idx) const
    {
        return nums[idx];
    }
    // ��ֵ�����
    BigInteger &operator=(const BigInteger &bInt)
    {
        if (bInt == *this)
            return *this;
        nums = bInt.nums;
        isPositive = bInt.isPositive;
        length = bInt.length;
        return *this;
    }
    BigInteger &operator=(BigInteger &&bInt) noexcept
    {
        nums = move(bInt.nums);
        isPositive = bInt.isPositive;
        length = bInt.length;
        return *this;
    }
    size_t size() const
    {
        return nums.size();
    }
    void cutLeadZero()
    {
        while (nums.size() > 1 && nums.back() == 0)
            nums.pop_back();
        if (nums.empty())
            length = 0;
        else
            length = (nums.size() - 1) * digit + to_string(nums.back()).size();
    }
    bool isZero() const
    {
        return nums.size() == 1 && nums.back() == 0;
    }
    BigInteger abs() const
    {
        return move(BigInteger(nums));
    }
    // ����10^n n<=0�᷵��1
    static BigInteger e(size_t n)
    {
        if (n <= 0)
            return move(BigInteger(vector<int>(1, 1)));
        ll m = n / digit;
        n -= m * digit;
        vector<int> ans(m);
        string s = "1";
        s += string(n, '0');
        ans.push_back(stoi(s));
        return move(BigInteger(ans));
    }

private:
    // ��λ����λ
    vector<int> nums;
    // ����λ
    bool isPositive = true;
    // λ��
    int length = 0;
    // nums�е�ÿһ��Ԫ�ش���digitλ����
    static int digit;
    static int mod;
};
int BigInteger::digit = 8;
int BigInteger::mod = 100000000;

int main()
{
    BigInteger a, b;
    cin >> a >> b;
    cout << a + b << '\n';
    cout << a * b << endl;
    return 0;
}
