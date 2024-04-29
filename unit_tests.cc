#include <gtest/gtest.h>

#include "SmartCalc2/model.h"

class ModelCalcTest : public ::testing::Test {
 protected:
  s21::Model calculator_test;
};

TEST_F(ModelCalcTest, Calculation1) {
  std::string str = "2+3*4";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 14.0);
}

TEST_F(ModelCalcTest, Calculation2) {
  std::string str = "2^2";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 4.0);
}

TEST_F(ModelCalcTest, Calculation3) {
  std::string str = "2^(1/2)";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 1.414214);
}

TEST_F(ModelCalcTest, Calculation4) {
  std::string str = "-3+5";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 2.0);
}

TEST_F(ModelCalcTest, Calculation5) {
  std::string str = "(2+3)*4";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 20.0);
}

TEST_F(ModelCalcTest, Calculation6) {
  std::string str = "1/(5^2+1)";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 0.038462);
}

TEST_F(ModelCalcTest, Calculation7) {
  std::string str = "sin(0.5*3.14)";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 1);
}

TEST_F(ModelCalcTest, Calculation8) {
  std::string str = "sin(cos(tan(5)))";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), -0.825786);
}

TEST_F(ModelCalcTest, Calculation9) {
  std::string str = "+-2";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), -2.0);
}

TEST_F(ModelCalcTest, Calculation10) {
  std::string str = "5---2";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 3.0);
}

TEST_F(ModelCalcTest, Calculation11) {
  std::string str = "sin(cos(tan(";
  std::string result = calculator_test.ModelCalc(str);
  ASSERT_NE(stod(result), sqrt(-1));
}

TEST_F(ModelCalcTest, Calculation12) {
  std::string str = "96%10";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 6.0);
}

TEST_F(ModelCalcTest, Calculation13) {
  std::string str = "atan(5)";
  std::string result = calculator_test.ModelCalc(str);
  ASSERT_NE(stod(result), sqrt(-1));
}

TEST_F(ModelCalcTest, Calculation14) {
  std::string str = "acos(5)";
  std::string result = calculator_test.ModelCalc(str);
  ASSERT_NE(stod(result), sqrt(-1));
}

TEST_F(ModelCalcTest, Calculation15) {
  std::string str = "asin(5)";
  std::string result = calculator_test.ModelCalc(str);
  ASSERT_NE(stod(result), sqrt(-1));
}

TEST_F(ModelCalcTest, Calculation16) {
  std::string str = "1e-2*1";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 0.01);
}

TEST_F(ModelCalcTest, Calculation17) {
  std::string str = "sqrt(log(10))";
  std::string result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 1.0);
  str = "ln(123)";
  result = calculator_test.ModelCalc(str);
  EXPECT_DOUBLE_EQ(stod(result), 4.812184);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
