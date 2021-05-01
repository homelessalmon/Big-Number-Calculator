#include"NumberObject.h"

using namespace std;

//NumberObject

ostream& operator<<(ostream& io, NumberObject num)
{
    if (num.point_index == 0)
    {
        if (num.positive == 1)
        {
            string temp = num.number;
            reverse(temp.begin(), temp.end());
            io << temp;
            return io;
        }
        else
        {
            if (num.positive == -1)
            {
                string temp = num.number;
                reverse(temp.begin(), temp.end());
                io << "-" << temp;
                return io;
            }
        }
    }
    else
    {
        if (num.positive == 1)
        {
            string temp = num.number;
            reverse(temp.begin(), temp.end());
            for (int i = 0; i < temp.length(); i++)
            {
                if (temp.length() - i == 100)
                {
                    cout << '.';
                }
                io << temp[i];
            }
            return io;
        }
        else
        {
            if (num.positive == -1)
            {
                string temp = num.number;
                int c = temp.length();
                reverse(temp.begin(), temp.end());
                io << "-";
                for (int i = 0; i < temp.length(); i++)
                {
                    if (temp.length() - i == 100)
                    {
                        cout << '.';
                    }
                    io << temp[i];
                }
                return io;
            }
        }
    }
}

//int

Integer::Integer()
{
    point_index = 0;
    positive = 1;
}

Integer::Integer(const Integer& reference)
{
    number = reference.number;
    point_index = reference.point_index;
    positive = reference.positive;
}

/*Integer& Integer::operator=(const Decimal&)
{
}*/

Integer operator+(const Integer& n1, const Integer& n2)
{
    string num1 = n1.number, num2 = n2.number;
    vector<int>ans;

    int num1_len = num1.length(), num2_len = num2.length();
    if (num1_len > num2_len) {
        swap(num1, num2);
        swap(num1_len, num2_len);
    }

    int carry = 0;
    for (int i = 0; i < num2_len; i++) {
        if (i < num1_len) {
            int t = (num1[i] - '0') + (num2[i] - '0') + carry;
            if (t >= 10) {
                carry = 1;
                t -= 10;
            }
            else carry = 0;
            ans.push_back(t);
        }
        else {
            int t = (num2[i] - '0') + carry;
            if (t >= 10) {
                carry = 1;
                t -= 10;
            }
            else carry = 0;
            ans.push_back(t);
        }
    }
    if (carry == 1) ans.push_back(1);

    string temp;
    for (int i = 0; i < ans.size(); i++) {
        temp.append(1, (char)(ans[i] + '0'));
    }

    Integer a;
    a.number = temp;
    a.positive = 1;
    return a;
}

Integer operator-(const Integer& n1, const Integer& n2)
{
    Integer a;
    string num1, num2;
    vector<int> ans;
    num1 = n1.number;
    num2 = n2.number;

    //check if the answer is positive
    if (num1.length() > num2.length()) {}
    else if (num2.length() > num1.length()) {
        swap(num1, num2);
        a.positive = -1;
    }
    else {
        for (int i = num1.length() - 1; i >= 0; i--) {
            if (num1[i] > num2[i]) {
                break;
            }
            if (num1[i] < num2[i]) {
                swap(num1, num2);
                a.positive = -1;
                break;
            }
        }
    }

    //substraction
    int borrow = 0, num1_len = num1.length(), num2_len = num2.length();
    for (int i = 0; i < num1_len; i++) {
        if (i < num2_len) {
            int t = (num1[i] - '0') - (num2[i] - '0') + borrow;
            if (t < 0) {
                borrow = -1;
                t += 10;
            }
            else borrow = 0;
            ans.push_back(t);
        }
        else {
            int t = (num1[i] - '0') + borrow;
            if (t < 0) {
                borrow = -1;
                t += 10;
            }
            else borrow = 0;
            ans.push_back(t);
        }
    }

    //clear redundant zeros ex.1000 - 999 = 0001 -> 1
    for (int i = ans.size() - 1; i > 0; i--) {
        if (ans[i] != 0)
            break;
        ans.pop_back();
    }

    string temp;
    for (int i = 0; i < ans.size(); i++) {
        temp.append(1, (char)(ans[i] + '0'));
    }

    a.number = temp;
    return a;
}

Integer operator*(const Integer& num1, const Integer& num2)
{
    if (num1.number == "0" || num2.number == "0")
    {
        Integer A;
        A.number = "0";
        A.positive = 1;
        return A;
    }
    vector<Integer> list_to_plus;
    for (int i = 0; i < num2.number.length(); i++)
    {
        int q = 0;
        string temp = num1.number;
        for (int j = 0; j < num1.number.length(); j++)
        {
            int c = ((temp[j] - '0') * (num2.number[i] - '0') + q) % 10;
            q = ((temp[j] - '0') * (num2.number[i] - '0') + q) / 10;
            temp[j] = c + '0';
            if (j == num1.number.length() - 1 && q > 0)
            {
                temp.append(1, q + '0');
            }
        }
        Integer A;
        A.number = temp;
        list_to_plus.push_back(A);
    }
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        string x = "";
        for (int j = 0; j < i; j++)
        {
            x.append(1, '0');
        }
        list_to_plus[i].number = x + list_to_plus[i].number;
    }
    Integer re;
    re.number = "0";
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        re = re + list_to_plus[i];
    }
    re.positive = num1.positive * num2.positive;
    return re;
}

Integer operator/(const Integer& num1, const Integer& num2)
{
    Decimal n1, n2;
    n1.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + num1.number; n2.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + num2.number;
    n1.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n1.number; n2.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n2.number;
    string t = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    if (n1.number == "0")
    {
        Integer X;
        X.number = "0";
        return X;
    }
    else
    {
        if (n2.number == "0")
        {
            Integer X;
            X.positive = 3;
            return X;
        }
    }
    if (num2.positive == 3)
    {
        Integer X;
        X.number = "0";
        return X;
    }
    while (n1.number.length() > n2.number.length())
    {
        t = "0" + t;
        n2.number = "0" + n2.number;
    }

    if (n1.number[n1.number.length() - 1] == '0') { n1.number.pop_back(); }
    if (n2.number[n2.number.length() - 1] == '0') { n2.number.pop_back(); }

    for (int i = t.length() - 1; i > -1; i--)
    {
        int m = 0;
        while (1)
        {
            Decimal A;
            A = n1 - n2;
            if (A.positive < 0) { break; }
            n1 = n1 - n2;
            m++;
        }
        t[i] = m + '0';
        m = 0;
        n2.number.erase(n2.number.begin());
        if (n2.number.length() < 101) { n2.number.append(1, '0'); }
    }
    while (t[t.length() - 1] == '0')
    {
        t.pop_back();
    }

    while (t.length() < 101)
    {
        t.append(1, '0');
    }
    Integer temp;
    temp.number = t.substr(100);
    temp.positive = num1.positive * num2.positive;
    return temp;
}

Integer factorial(const Integer& num)
{
    Integer one; one.number = "1";
    Integer s = one, now = num;
    if (num.number == "0")
    {
        return one;
    }
    while (now.number != one.number)
    {
        s = s * now;
        now = now - one;
    }
    return s;
}

Integer power(const Integer& base, const Integer& exp)
{
    Integer s = base, temp = exp, one; one.number = "1";
    if (exp.number == "0" || exp.positive == -1) { Integer tmp; tmp.number = "1"; return tmp; }
    while (temp.number != "1") { s = s * base; temp = temp - one; }
    return s;
}

Integer power(const Integer& base, const Decimal& exp)
{
    Decimal b, e = exp, one, two, zero; b.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + base.number;
    zero.number.insert(0, 101, '0'); one.number.insert(0, 100, '0'); one.number.append(1, '1'); two = one + one;
    if (exp.number == zero.number) { return one; }
    if (b.number == "0") { return zero; }
    if (exp.positive == -1) { return zero; }

    bool check = false;
    for_each(exp.number.begin(), exp.number.begin() + 98, [&check](char n) {if (n != '0') { check = true; }});
    if (exp.number[99] != '5' && exp.number[99] != '0') { check = true; }
    if (check) { Decimal X; X.positive = 3; return X; }

    if (exp.number[99] == '5')
    {
        if (base.positive == -1) { Decimal X; X.positive = 3; return X; }
        e = e * two;
        Decimal re = b;
        while (e.number != one.number)
        {
            re = re * base;
            e = e - one;
        }
        Decimal next, now = re / two; next.number = "0";
        while (next.number != now.number)
        {
            next = ((now * now) + re) / (two * now);
            swap(next, now);
        }
        if (exp.positive == -1)
        {
            return one / now;
        }
        else
        {
            if (exp.positive == 1)
            {
                return now;
            }
        }
    }
    else
    {
        Decimal re = b;

        while (e.number != one.number)
        {
            re = re * base;
            e = e - one;
        }
        if (exp.positive == -1)
        {
            return one / re;
        }
        else
        {
            if (exp.positive == 1)
            {
                return re;
            }
        }
    }

}


void Integer::operator=(const NumberObject& input) {
    number = input.number;
    positive = input.positive;
    point_index = input.point_index;
}

Integer Integer::operator-()
{
    if (this->number != "0") {
        this->positive *= -1;
    }
    return *this;
}

Integer::operator Decimal()
{
    Decimal temp;
    string str = this->number;
    temp.positive = this->positive;
    temp.number = str.insert(0, 100, '0');
    return temp;
}

//-------------------------------------------------------------------------
//Decimal

Decimal::Decimal()
{
    point_index = 1; positive = 1;
}

Decimal::Decimal(const Decimal& reference)
{
    number = reference.number;
    point_index = reference.point_index;
    positive = reference.positive;
}

bool operator>(const Decimal& n1, const Decimal& n2)
{
    if (n1.positive == -1 && n2.positive == 1)
    {
        return false;
    }
    if (n1.number.length() > n2.number.length())
    {
        return true;
    }
    else if (n1.number.length() < n2.number.length())
    {
        return false;
    }
    else {
        for (int i = n1.number.length() - 1; i >= 0; i--)
        {
            if (n2.number[i] > n1.number[i])
            {
                return false;
            }
        }
    }
    return true;
}

Decimal operator+(const Decimal& n1, const Integer& n2)
{
    string num1 = n1.number, num2 = n2.number;
    num2.insert(0, 100, '0');
    vector<int>ans;

    int num1_len = num1.length(), num2_len = num2.length();
    if (num1_len > num2_len) {
        swap(num1, num2);
        swap(num1_len, num2_len);
    }

    int carry = 0;
    for (int i = 0; i < num2_len; i++) {
        if (i < num1_len) {
            int t = (num1[i] - '0') + (num2[i] - '0') + carry;
            if (t >= 10) {
                carry = 1;
                t -= 10;
            }
            else carry = 0;
            ans.push_back(t);
        }
        else {
            int t = (num2[i] - '0') + carry;
            if (t >= 10) {
                carry = 1;
                t -= 10;
            }
            else carry = 0;
            ans.push_back(t);
        }
    }
    if (carry == 1) ans.push_back(1);

    string temp;
    for (int i = 0; i < ans.size(); i++) {
        temp.append(1, (char)(ans[i] + '0'));
    }

    Decimal a;
    a.number = temp;
    a.positive = 1;
    return a;
}

Decimal operator-(const Decimal& n1, const Integer& n2)
{
    Decimal a;
    string num1, num2;
    vector<int> ans;
    num1 = n1.number;
    num2 = n2.number;
    num2.insert(0, 100, '0');

    //check if the answer is positive
    if (num1.length() > num2.length()) {}
    else if (num2.length() > num1.length()) {
        swap(num1, num2);
        a.positive = -1;
    }
    else {
        for (int i = num1.length() - 1; i >= 0; i--) {
            if (num1[i] > num2[i]) {
                break;
            }
            if (num1[i] < num2[i]) {
                swap(num1, num2);
                a.positive = -1;
                break;
            }
        }
    }

    //substraction
    int borrow = 0, num1_len = num1.length(), num2_len = num2.length();
    for (int i = 0; i < num1_len; i++) {
        if (i < num2_len) {
            int t = (num1[i] - '0') - (num2[i] - '0') + borrow;
            if (t < 0) {
                borrow = -1;
                t += 10;
            }
            else borrow = 0;
            ans.push_back(t);
        }
        else {
            int t = (num1[i] - '0') + borrow;
            if (t < 0) {
                borrow = -1;
                t += 10;
            }
            else borrow = 0;
            ans.push_back(t);
        }
    }

    //clear redundant zeros ex.1000 - 999 = 0001 -> 1
    for (int i = ans.size() - 1; i > 0; i--) {
        if (ans[i] != 0)
            break;
        ans.pop_back();
    }

    string temp;
    for (int i = 0; i < ans.size(); i++) {
        temp.append(1, (char)(ans[i] + '0'));
    }

    a.number = temp;
    return a;
}

Decimal operator*(const Decimal& num1, const Integer& num2)
{
    string zero = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    if (num1.number == zero || num2.number == "0") {
        Decimal A;
        A.number = zero;
        A.positive = 1;
        return A;
    }
    vector<Integer> list_to_plus;
    for (int i = 0; i < num2.number.length(); i++)
    {
        int q = 0;
        string temp = num1.number;
        for (int j = 0; j < num1.number.length(); j++)
        {
            int c = ((temp[j] - '0') * (num2.number[i] - '0') + q) % 10;
            q = ((temp[j] - '0') * (num2.number[i] - '0') + q) / 10;
            temp[j] = c + '0';
            if (j == num1.number.length() - 1 && q > 0)
            {
                temp.append(1, q + '0');
            }
        }
        Integer A;
        A.number = temp;
        list_to_plus.push_back(A);
    }
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        string x = "";
        for (int j = 0; j < i; j++)
        {
            x.append(1, '0');
        }
        list_to_plus[i].number = x + list_to_plus[i].number;
    }
    Decimal re;
    re.number = "0";
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        re = re + list_to_plus[i];
    }
    re.positive = num1.positive * num2.positive;
    re.number = re.number.substr(100);
    return re;
}

Decimal operator/(const Decimal& num1, const Integer& num2)
{
    Decimal n1 = num1, n2; n2.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + num2.number;
    n1.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n1.number; n2.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n2.number;
    string t = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    if (num1.number == t)
    {
        Decimal X;
        X.number = t;
        return X;
    }
    else
    {
        if (num2.number == "0")
        {
            Decimal X;
            X.positive == 3;
            return X;
        }
    }
    if (num2.positive == 3)
    {
        Decimal X;
        X.number = t;
        return X;
    }
    while (n1.number[n1.number.length() - 1] == '0')
    {
        n1.number.pop_back();
        n1.number = "0" + n1.number;
        n2.number = "0" + n2.number;
    }
    while (n2.number[n2.number.length() - 1] == '0')
    {
        n2.number.pop_back();
        n2.number = "0" + n2.number;
        n1.number = "0" + n1.number;
    }
    while (n1.number.length() > n2.number.length())
    {
        t = "0" + t;
        n2.number = "0" + n2.number;
    }

    for (int i = t.length() - 1; i > -1; i--)
    {
        int m = 0;
        while (1)
        {
            Decimal A;
            A = n1 - n2;
            if (A.positive < 0) { break; }
            n1 = n1 - n2;
            m++;
        }
        t[i] = m + '0';
        m = 0;
        n2.number.erase(n2.number.begin());
        if (n2.number.length() < 101) { n2.number.append(1, '0'); }
    }
    while (t[t.length() - 1] == '0')
    {
        t.pop_back();
    }

    while (t.length() < 101)
    {
        t.append(1, '0');
    }
    Decimal temp;
    temp.number = t;
    temp.positive = num1.positive * num2.positive;
    return temp;
}

Decimal operator+(const Integer& n1, const Decimal& n2)
{
    string num1 = n1.number, num2 = n2.number;
    num1.insert(0, 100, '0');
    vector<int>ans;

    int num1_len = num1.length(), num2_len = num2.length();
    if (num1_len > num2_len) {
        swap(num1, num2);
        swap(num1_len, num2_len);
    }

    int carry = 0;
    for (int i = 0; i < num2_len; i++) {
        if (i < num1_len) {
            int t = (num1[i] - '0') + (num2[i] - '0') + carry;
            if (t >= 10) {
                carry = 1;
                t -= 10;
            }
            else carry = 0;
            ans.push_back(t);
        }
        else {
            int t = (num2[i] - '0') + carry;
            if (t >= 10) {
                carry = 1;
                t -= 10;
            }
            else carry = 0;
            ans.push_back(t);
        }
    }
    if (carry == 1) ans.push_back(1);

    string temp;
    for (int i = 0; i < ans.size(); i++) {
        temp.append(1, (char)(ans[i] + '0'));
    }

    Decimal a;
    a.number = temp;
    a.positive = 1;
    return a;
}

Decimal operator-(const Integer& n1, const Decimal& n2)
{
    Decimal a;
    string num1, num2;
    vector<int> ans;
    num1 = n1.number;
    num2 = n2.number;
    num1.insert(0, 100, '0');

    //check if the answer is positive
    if (num1.length() > num2.length()) {}
    else if (num2.length() > num1.length()) {
        swap(num1, num2);
        a.positive = -1;
    }
    else {
        for (int i = num1.length() - 1; i >= 0; i--) {
            if (num1[i] > num2[i]) {
                break;
            }
            if (num1[i] < num2[i]) {
                swap(num1, num2);
                a.positive = -1;
                break;
            }
        }
    }

    //substraction
    int borrow = 0, num1_len = num1.length(), num2_len = num2.length();
    for (int i = 0; i < num1_len; i++) {
        if (i < num2_len) {
            int t = (num1[i] - '0') - (num2[i] - '0') + borrow;
            if (t < 0) {
                borrow = -1;
                t += 10;
            }
            else borrow = 0;
            ans.push_back(t);
        }
        else {
            int t = (num1[i] - '0') + borrow;
            if (t < 0) {
                borrow = -1;
                t += 10;
            }
            else borrow = 0;
            ans.push_back(t);
        }
    }

    //clear redundant zeros ex.1000 - 999 = 0001 -> 1
    for (int i = ans.size() - 1; i > 0; i--) {
        if (ans[i] != 0)
            break;
        ans.pop_back();
    }

    string temp;
    for (int i = 0; i < ans.size(); i++) {
        temp.append(1, (char)(ans[i] + '0'));
    }

    a.number = temp;
    return a;
}

Decimal operator*(const Integer& num1, const Decimal& num2)
{
    string zero = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    if (num1.number == "0" || num2.number == zero) {
        Decimal A;
        A.number = zero;
        A.positive = 1;
        return A;
    }
    vector<Integer> list_to_plus;
    for (int i = 0; i < num2.number.length(); i++)
    {
        int q = 0;
        string temp = num1.number;
        for (int j = 0; j < num1.number.length(); j++)
        {
            int c = ((temp[j] - '0') * (num2.number[i] - '0') + q) % 10;
            q = ((temp[j] - '0') * (num2.number[i] - '0') + q) / 10;
            temp[j] = c + '0';
            if (j == num1.number.length() - 1 && q > 0)
            {
                temp.append(1, q + '0');
            }
        }
        Integer A;
        A.number = temp;
        list_to_plus.push_back(A);
    }
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        string x = "";
        for (int j = 0; j < i; j++)
        {
            x.append(1, '0');
        }
        list_to_plus[i].number = x + list_to_plus[i].number;
    }
    Decimal re;
    re.number = "0";
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        re = re + list_to_plus[i];
    }
    re.positive = num1.positive * num2.positive;
    re.number = re.number.substr(100);
    return re;
}

Decimal operator/(const Integer& num1, const Decimal& num2)
{
    Decimal n1, n2 = num2; n1.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + num1.number;
    n1.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n1.number; n2.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n2.number;
    string t = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    if (num1.number == "0")
    {
        Decimal X;
        X.number = t;
        return X;
    }
    else
    {
        if (num2.number == t)
        {
            Decimal X;
            X.positive == 3;
            return X;
        }
    }
    if (num2.positive == 3)
    {
        Decimal X;
        X.number = t;
        return X;
    }
    while (n1.number[n1.number.length() - 1] == '0')
    {
        n1.number.pop_back();
        n1.number = "0" + n1.number;
        n2.number = "0" + n2.number;
    }
    while (n2.number[n2.number.length() - 1] == '0')
    {
        n2.number.pop_back();
        n2.number = "0" + n2.number;
        n1.number = "0" + n1.number;
    }
    while (n1.number.length() > n2.number.length())
    {
        t = "0" + t;
        n2.number = "0" + n2.number;
    }

    for (int i = t.length() - 1; i > -1; i--)
    {
        int m = 0;
        while (1)
        {
            Decimal A;
            A = n1 - n2;
            if (A.positive < 0) { break; }
            n1 = n1 - n2;
            m++;
        }
        t[i] = m + '0';
        m = 0;
        n2.number.erase(n2.number.begin());
        if (n2.number.length() < 101) { n2.number.append(1, '0'); }
    }
    while (t[t.length() - 1] == '0')
    {
        t.pop_back();
    }

    while (t.length() < 101)
    {
        t.append(1, '0');
    }
    Decimal temp;
    temp.number = t;
    temp.positive = num1.positive * num2.positive;
    return temp;
}

Decimal operator+(const Decimal& n1, const Decimal& n2)
{
    string num1 = n1.number, num2 = n2.number;
    vector<int>ans;

    int num1_len = num1.length(), num2_len = num2.length();
    if (num1_len > num2_len) {
        swap(num1, num2);
        swap(num1_len, num2_len);
    }

    int carry = 0;
    for (int i = 0; i < num2_len; i++) {
        if (i < num1_len) {
            int t = (num1[i] - '0') + (num2[i] - '0') + carry;
            if (t >= 10) {
                carry = 1;
                t -= 10;
            }
            else carry = 0;
            ans.push_back(t);
        }
        else {
            int t = (num2[i] - '0') + carry;
            if (t >= 10) {
                carry = 1;
                t -= 10;
            }
            else carry = 0;
            ans.push_back(t);
        }
    }
    if (carry == 1) ans.push_back(1);

    string temp;
    for (int i = 0; i < ans.size(); i++) {
        temp.append(1, (char)(ans[i] + '0'));
    }

    Decimal a;
    a.number = temp;
    a.positive = 1;
    return a;
}

Decimal operator-(const Decimal& n1, const Decimal& n2)
{
    Decimal a;
    string num1, num2;
    vector<int> ans;
    num1 = n1.number;
    num2 = n2.number;

    //check if the answer is positive
    if (num1.length() > num2.length()) {}
    else if (num2.length() > num1.length()) {
        swap(num1, num2);
        a.positive = -1;
    }
    else {
        for (int i = num1.length() - 1; i >= 0; i--) {
            if (num1[i] > num2[i]) {
                break;
            }
            if (num1[i] < num2[i]) {
                swap(num1, num2);
                a.positive = -1;
                break;
            }
        }
    }

    //substraction
    int borrow = 0, num1_len = num1.length(), num2_len = num2.length();
    for (int i = 0; i < num1_len; i++) {
        if (i < num2_len) {
            int t = (num1[i] - '0') - (num2[i] - '0') + borrow;
            if (t < 0) {
                borrow = -1;
                t += 10;
            }
            else borrow = 0;
            ans.push_back(t);
        }
        else {
            int t = (num1[i] - '0') + borrow;
            if (t < 0) {
                borrow = -1;
                t += 10;
            }
            else borrow = 0;
            ans.push_back(t);
        }
    }

    //clear redundant zeros ex.1000 - 999 = 0001 -> 1
    for (int i = ans.size() - 1; i > 0; i--) {
        if (ans[i] != 0)
            break;
        ans.pop_back();
    }

    string temp;
    for (int i = 0; i < ans.size(); i++) {
        temp.append(1, (char)(ans[i] + '0'));
    }
    while (temp.length() < 101)
    {
        temp.append(1, '0');
    }

    a.number = temp;
    return a;
}

Decimal operator*(const Decimal& num1, const Decimal& num2)
{
    string zero = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    if (num1.number == zero || num2.number == zero) {
        Decimal A;
        A.number = zero;
        A.positive = 1;
        return A;
    }
    vector<Integer> list_to_plus;
    for (int i = 0; i < num2.number.length(); i++)
    {
        int q = 0;
        string temp = num1.number;
        for (int j = 0; j < num1.number.length(); j++)
        {
            int c = ((temp[j] - '0') * (num2.number[i] - '0') + q) % 10;
            q = ((temp[j] - '0') * (num2.number[i] - '0') + q) / 10;
            temp[j] = c + '0';
            if (j == num1.number.length() - 1 && q > 0)
            {
                temp.append(1, q + '0');
            }
        }
        Integer A;
        A.number = temp;
        list_to_plus.push_back(A);
    }
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        string x = "";
        for (int j = 0; j < i; j++)
        {
            x.append(1, '0');
        }
        list_to_plus[i].number = x + list_to_plus[i].number;
    }
    Decimal re;
    re.number = "0";
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        re = re + list_to_plus[i];
    }
    re.number = re.number.substr(200);
    re.positive = num1.positive * num2.positive;
    return re;
}

Decimal operator/(const Decimal& num1, const Decimal& num2)
{
    
    Decimal n1 = num1, n2 = num2;
    n1.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n1.number; n2.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n2.number;
    string t = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    if (num1.number == t)
    {
        Decimal X;
        X.number = t;
        return X;
    }
    else
    {
        if (num2.number == t)
        {
            Decimal X;
            X.positive == 3;
            return X;
        }
    }
    if (num2.positive == 3)
    {
        Decimal X;
        X.number = t;
        return X;
    }
    while (n1.number[n1.number.length() - 1] == '0')
    {
        n1.number.pop_back();
        n1.number = "0" + n1.number;
        n2.number = "0" + n2.number;
    }
    while (n2.number[n2.number.length() - 1] == '0')
    {
        n2.number.pop_back();
        n2.number = "0" + n2.number;
        n1.number = "0" + n1.number;
    }
    while (n1.number.length() > n2.number.length())
    {
        t = "0" + t;
        n2.number = "0" + n2.number;
    }

    for (int i = t.length() - 1; i > -1; i--)
    {
        int m = 0;
        while (1)
        {
            Decimal A;
            A = n1 - n2;
            if (A.positive < 0) { break; }
            n1 = n1 - n2;
            m++;
        }
        t[i] = m + '0';
        m = 0;
        n2.number.erase(n2.number.begin());
        if (n2.number.length() < 101) { n2.number.append(1, '0'); }
    }
    while (t[t.length() - 1] == '0')
    {
        t.pop_back();
    }

    while (t.length() < 101)
    {
        t.append(1, '0');
    }
    Decimal temp;
    temp.number = t;
    temp.positive = num1.positive * num2.positive;
    return temp;
}

Decimal factorial(const Decimal& num)
{
    bool check = false;
    for_each(num.number.begin(), num.number.begin() + 99, [&check](char w) {if (w != '0') { check = true; }});
    if (check)
    {
        Decimal X; X.positive = 2; return X;
    }
    Decimal one; one.number = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
    Decimal s = one, now = num;
    if (num.number == "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")
    {
        return one;
    }
    while (now.number != one.number)
    {
        s = s * now;
        now = now - one;
    }
    return s;
}

Decimal power(const Decimal& base, const Integer& exp)
{
    Decimal zero, one; zero.number = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"; one.number = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
    if (exp.number == "0") { return one; }
    if (base.number == zero.number) { return zero; }
    Decimal re = base; Integer tmp = exp;
    while (tmp.number != "1") { re = re * base; tmp = tmp - one; }
    if (exp.positive == 1)
    {
        return re;
    }
    else
    {
        if (exp.positive == -1)
        {
            return one / re;
        }
    }
}

Decimal power(const Decimal& base, const Decimal& exp)
{
    Decimal b = base, e = exp, one, two, zero;
    zero.number.insert(0, 101, '0'); one.number.insert(0, 100, '0'); one.number.append(1, '1'); two = one + one;
    if (exp.number == zero.number) { return one; }
    if (b.number == zero.number) { return zero; }

    bool check = false;
    for_each(exp.number.begin(), exp.number.begin() + 98, [&check](char n) {if (n != '0') { check = true; }});
    if (exp.number[99] != '5' && exp.number[99] != '0') { check = true; }
    if (check) { Decimal X; X.positive = 3; return X; }
    
    if (exp.number[99] == '5')
    {
        if(base.positive==-1){ Decimal X; X.positive = 3; return X; }
        e = e * two;
        Decimal re = base;
        while (e.number != one.number)
        {
            re = re * base;
            e = e - one;
        }
        Decimal next, now = re / two; next.number = "0";
        while (next.number != now.number)
        {
            next = ((now * now) + re) / (two * now);
            swap(next, now);
        }
        if (exp.positive == -1)
        {
            return one / now;
        }
        else
        {
            if (exp.positive == 1)
            {
                return now;
            }
        }
    }
    else
    {
        Decimal re = base;
        while (e.number != one.number)
        {
            re = re * base;
            e = e - one;
        }
        if (exp.positive == -1)
        {
            return one / re;
        }
        else
        {
            if (exp.positive == 1)
            {
                return re;
            }
        }
    }
}

void Decimal::operator=(const NumberObject& input) {
    number = input.number;
    positive = input.positive;
    point_index = input.point_index;
}

Decimal Decimal::operator-()
{
    if (this->number != "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000") {
        this->positive *= -1;
    }
    return *this;
}

Decimal::operator Integer()
{
    Integer tmp;
    string str = this->number;
    if (str.back() == '0')
        tmp.positive = 1;
    else
        tmp.positive = this->positive;
    tmp.number = str.substr(100);
    return tmp;
}

NumberObject::NumberObject(int error_code) {
    positive = error_code;
    number = "";
    point_index = 0;
}
