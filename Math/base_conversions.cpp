string letters = "0123456789ABCDEF"; //hexadecimal
int toInt(char c)
{
	return letters.find(c);
}

int fromAnyBaseToDecimal(string& in, int base)
{
	int ret = 0;
	for(int i = 0; i<in.size(); i++){
		ret *= base, ret += toInt(in[i]);
	}
	return ret;
}

string fromDecimalToAnybase(int number, int base)
{
	if(number == 0) return "0";
	string ret = "";

	while(number)
	{
		ret = letters[number % base] + ret;
		number/= base;
	}

	return ret;
}
