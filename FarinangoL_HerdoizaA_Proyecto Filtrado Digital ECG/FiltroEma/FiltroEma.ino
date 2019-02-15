float EMA_ALPHA = 0.6;
int EMA_LP = 0;
int EMA_HP = 0;
 
int values[] = {110,
108,
102,
104,
96,
100,
92,
69,
28,
11,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
11,
81,
68,
82,
112,
109,
110,
108,
102,
104,
96,
100,
92,
69,
28,
11,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
36,
39,
38,
15,
29,
24,
26,
27,
21,
22,
20,
18,
20,
37,
56,
65,
63,
72,
59,
59,
75,
82,
81,
79,
76,
72,
68,
65,
52,
59,
63,
64,
44,
32,
61,
27,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
8,
21,
30,
32,
30,
34,
32,
31,
29,
27,
11,
19,
26,
24,
22,
22,
20,
18,
16,
19,
12,
17,
18,
21,
22,
19,
20,
19,
18,
21,
29,
46,
55,
57,
56,
54,
56,
59,
61,
60,
61,
57,
57,
57,
53,
51,
50,
46,
36,
21,
5,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
3,
21,
28,
30,
32,
32,
33,
31,
31,
11,
18,
27,
29,
24,
25,
22,
22,
21,
20,
14,
17,
20,
22,
23,
20,
22,
20,
22,
22,
38,
53,
60,
59,
57,
56,
62,
63,
62,
61,
58,
53,
53,
48,
45,
47,
34,
25,
23,
9,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
16,
29,
32,
32,
34,
31,
34,
32,
26,
14,
26,
25,
26,
24,
24,
23,
19,
20,
15,
16,
21,
19,
22,
20,
22,
21,
21,
23,
32,
48,
57,
59,
57,
53,
57,
59,
58,
57,
54,
54,
52,
49,
43,
45,
45,
40,
31,
17,
4,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
2,
33,
47,
56,
58,
59,
57,
51,
52,
48,
16,
27,
31,
37,
34,
30,
28,
25,
24,
18,
16,
19,
16,
19,
30,
25,
25,
24,
25,
27,
30,
50,
71,
80,
86,
83,
78,
80,
91,
84,
83,
85,
80,
79,
80,
78,
75,
72,
69,
49,
44,
10,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
10,
31,
42,
46,
48,
47,
44,
43,
46,
39,
20,
19,
28,
30,
27,
27,
27,
23,
20,
18,
20,
13,
15,
17,
17,
23,
23,
24,
26,
25,
25,
26,
47,
70,
79,
83,
85,
81,
78,
86,
85,
89,
88,
88,
87,
84,
82,
79,
78,
77,
81,
68,
49,
24,
17,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
};
int valuesLength = sizeof(values) / sizeof(int);

int getMeasure()
{
   int static index = 0;
   index++;
   return values[index - 1];
}
 
void setup()
{
   Serial.begin(9600);
 for (int iCount = 0; iCount < valuesLength; iCount++)
   {
      int value = getMeasure();
      int filteredLP = EMALowPassFilter(value);
      int filteredHP = EMAHighPassFilter(value);
      Serial.print(value+1);
      Serial.print(",");
      Serial.print(filteredLP+5);
      Serial.print(",");
      Serial.println(filteredHP+10);
}
   
  
}

void loop()
{
   
   delay(10000);
}
 
int EMALowPassFilter(int value)
{
   EMA_LP = EMA_ALPHA * value + (1 - EMA_ALPHA) * EMA_LP;
   return EMA_LP;
}
 
int EMAHighPassFilter(int value)
{
   EMA_LP = EMA_ALPHA * value + (1 - EMA_ALPHA) * EMA_LP;
   EMA_HP = value - EMA_LP;
 
   return EMA_HP;
}