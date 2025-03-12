#include <iostream>
#include <cmath>
using namespace std;

const int MAX_TERMS = 100; // 假設最多有100項 

class Polynomial {
private:
    int** terms; // 動態二維陣列，儲存係數和次方
    int numberOfTerms; // 儲存多項式的項數

public:
    Polynomial() : numberOfTerms(0) { //動態分配且初始化每個項目 
        terms = new int*[MAX_TERMS];
        for (int i = 0; i < MAX_TERMS; ++i) {
            terms[i] = new int[2](); 
        }
    }

    ~Polynomial() { //釋放記憶體 
        for (int i = 0; i < MAX_TERMS; ++i) {
            delete[] terms[i];
        }
        delete[] terms;
    }

    void inputPolynomial() { //輸入函式 
        int exponent, coefficient;
        cout << "輸入係數、指數(直到 0 0 結束):" << endl;

        while (true) { //持續依照係數、次方輸入至陣列中  
            cin >> coefficient >> exponent;
            if (exponent == 0 && coefficient == 0) break; // 0 0 結束輸入
            if (numberOfTerms < MAX_TERMS) {
                terms[numberOfTerms][0] = coefficient; // 係數
                terms[numberOfTerms][1] = exponent; // 次方
                ++numberOfTerms;
            }
        }
    }

    void displayPolynomial() const { //顯示函式，輸出多項式 
        bool firstTerm = true;
        for (int i = 0; i < numberOfTerms; ++i) {
            if (terms[i][0] != 0) { //當係數不為0則輸出  
                if (!firstTerm) cout << " + "; //一開始為TRUE不需要+號 
                cout << terms[i][0]; //輸出係數 
                if (terms[i][1] > 0) cout << "x^" << terms[i][1]; 
//次方大於0才需要顯示X^ 
                firstTerm = false;  
            }
        }
        if (firstTerm) cout << "0";
        cout << endl;
    }

    Polynomial operator+(const Polynomial &other) const { //相加函式 
        Polynomial result;
        int i = 0, j = 0;

        while (i < numberOfTerms && j < other.numberOfTerms) { 
//持續運算直到超過陣列大小  
            if (terms[i][1] == other.terms[j][1]) { //若次方相同則相加  
                result.terms[result.numberOfTerms][0] = terms[i][0] + other.terms[j][0];
                result.terms[result.numberOfTerms][1] = terms[i][1];
                ++i;
                ++j;
            } else if (terms[i][1] > other.terms[j][1]) { //先存入較大的次方  
                result.terms[result.numberOfTerms][0] = terms[i][0];
                result.terms[result.numberOfTerms][1] = terms[i][1];
                ++i;
            } else {
                result.terms[result.numberOfTerms][0] = other.terms[j][0];
                result.terms[result.numberOfTerms][1] = other.terms[j][1];
                ++j;
            }
            ++result.numberOfTerms;
        }
		//處理剩下的多項式 ，入無法相加的多項式 (單獨項)  
        while (i < numberOfTerms) {
            result.terms[result.numberOfTerms][0] = terms[i][0];
            result.terms[result.numberOfTerms][1] = terms[i][1];
            ++i;
            ++result.numberOfTerms;
        }

        while (j < other.numberOfTerms) {
            result.terms[result.numberOfTerms][0] = other.terms[j][0];
            result.terms[result.numberOfTerms][1] = other.terms[j][1];
            ++j;
            ++result.numberOfTerms;
        }

        return result;
    }

    Polynomial operator*(const Polynomial &other) const { //乘法函式  
        Polynomial result;

        for (int i = 0; i < numberOfTerms; ++i) { //雙迴圈跑過每個陣列並且相乘  
            for (int j = 0; j < other.numberOfTerms; ++j) {
                int coefficient = terms[i][0] * other.terms[j][0]; //係數相乘  
                int exponent = terms[i][1] + other.terms[j][1]; //次方相加 
                bool termExists = false;

                for (int k = 0; k < result.numberOfTerms; ++k) {  
//檢查是否有相同次方的項
                    if (result.terms[k][1] == exponent) {  //如果次方相同則相加 
                        result.terms[k][0] += coefficient;
                        termExists = true;
                        break;
                    }
                }

                if (!termExists && result.numberOfTerms < MAX_TERMS) { 
//如果沒有相同次方的項目則新增  
                    result.terms[result.numberOfTerms][0] = coefficient;
                    result.terms[result.numberOfTerms][1] = exponent;
                    ++result.numberOfTerms;
                }
            }
        }

        return result;
    }

    double Eval(double x) const { //帶入x計算數值  
        double result = 0.0;
        for (int i = 0; i < numberOfTerms; ++i) {
            result += terms[i][0] * pow(x, terms[i][1]); 
//係數乘上x次方(使用pow函式)  
        }
        return result;
    }
	//顯示函式，依照格式輸出 
    void printEval(const Polynomial &poly2, double x, double poly1Value, double poly2Value) const {
        cout << "Polynomial 1 p(" << x << ") = ";
        displayPolynomial();
        cout << " = " << poly1Value << endl;

        cout << "Polynomial 2 p(" << x << ") = ";
        poly2.displayPolynomial();
        cout << " = " << poly2Value << endl;
    }
};

int main() {
    Polynomial poly1, poly2, sum, product;
	//呼叫函式，輸入數值 
    poly1.inputPolynomial();
    poly2.inputPolynomial();
    double x;  
    cout << "輸入 x : ";
    cin >> x;
	//呼叫函式輸出整理後的多項式 
    cout << "Polynomial 1 p(x) = ";
    poly1.displayPolynomial();
    cout << endl;
    cout << "Polynomial 2 p(x) = ";
    poly2.displayPolynomial();
    cout << endl;
	//呼叫函式，輸出相加後的多項式 
    sum = poly1 + poly2;
    cout << "Add : Polynomial 1 + Polynomial 2 = ";
    sum.displayPolynomial();
    cout << endl;
	//呼叫函式，輸出相乘整理後的多項式 
    product = poly1 * poly2;
    cout << "Mult : Polynomial 1 * Polynomial 2 = ";
    product.displayPolynomial();
    cout << endl;
	//呼叫函式，輸出帶入x計算的值 
    double poly1Value = poly1.Eval(x);
    double poly2Value = poly2.Eval(x);
	//輸出函式 
	cout << "Eval:" << endl;
    poly1.printEval(poly2, x, poly1Value, poly2Value);

    return 0;
}
