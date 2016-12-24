#include<bits/stdc++.h>
using namespace std;
int rma=0;
bool isoperation( char a )
{
	if( a=='*' || a=='+' || a=='-' || a=='/' || a=='^' )
		return true;
	return false;
}
bool canskip( string MyString )
{
	int Open=0;
	if( MyString[0]!='(' )return false;
	for( int i=0;i<MyString.size();i++ )
	{
		if( MyString[i]=='(' )Open++;
		else if( MyString[i]==')' )Open--;
		if( Open==0 && i!=MyString.size()-1 )return false;
	}
	return true;
}
int Number_Operation( string MyString )
{
	int nmb=0;
	int Open=0;
	for( int i=0;i<MyString.size();i++ )
	{
		if( MyString[i]=='(' )Open++;
		else if( MyString[i]==')' )Open--;
		if( Open==0 && isoperation(MyString[i]) )nmb++;
	}
	return nmb;
}
bool Number( string MyString )
{
	for( int i=0;i<MyString.size();i++ )
	{
		if( !isdigit(MyString[i]) )return false;
	}
	return true;
}
string Take_Derivative( string MyString );
string Take2( int pos,string MyString )
{
	string result="";
	for( int i=pos;i<MyString.size();i++ )
	{
		result+=MyString[i];
	}
	return result;
}
string Derivative( string MyString )
{
    if( MyString.size()==0 )return "";
	if( canskip(MyString) )
	{
		string NewString="";
		for( int i=1;i<MyString.size()-1;i++ )NewString+=MyString[i];
		return "("+Derivative(NewString)+")";
	}
	if( MyString.size()==1 && MyString[0]=='x' )return "(1)";
	if( Number(MyString) )return "(0)";
    if( MyString.size()>=2 && MyString[0]=='l' && MyString[1]=='n' )return "((1/"+Take2(2,MyString)+")*"+Take_Derivative(Take2(2,MyString))+")";
    if( MyString.size()>=2 && MyString[0]=='t' && MyString[1]=='g' )return "(((1/cos"+Take2(2,MyString)+"^2))*"+Take_Derivative(Take2(2,MyString))+")";
    if( MyString.size()>=3 && MyString[0]=='s' && MyString[1]=='i' && MyString[2]=='n' )return "((cos"+Take2(3,MyString)+")*"+Take_Derivative(Take2(3,MyString))+")";
    if( MyString.size()>=3 && MyString[0]=='c' && MyString[1]=='o' && MyString[2]=='s' )return "((-sin"+Take2(3,MyString)+")*"+Take_Derivative(Take2(3,MyString))+")";
    if( MyString.size()>=3 && MyString[0]=='c' && MyString[1]=='t' && MyString[2]=='g' )return "((-1/(sin"+Take2(3,MyString)+"^2))*"+Take_Derivative(Take2(3,MyString))+")";
    if( MyString.size()>=5 && MyString[0]=='a' && MyString[1]=='r' && MyString[2]=='c' && MyString[3]=='t' && MyString[4]=='g' )return "((1/(1+"+Take2(5,MyString)+"^2))*"+Take_Derivative(Take2(5,MyString))+")";
    if( MyString.size()>=6 && MyString[0]=='a' && MyString[1]=='r' && MyString[2]=='c' && MyString[3]=='c' && MyString[4]=='t' && MyString[5]=='g' )return "((-1/(1+"+Take2(6,MyString)+"^2))*"+Take_Derivative(Take2(6,MyString))+")";
    if( MyString.size()>=6 && MyString[0]=='a' && MyString[1]=='r' && MyString[2]=='c' && MyString[3]=='s' && MyString[4]=='i' && MyString[5]=='n' )return "((1/((1-"+Take2(6,MyString)+"^2)^(1/2)))*"+Take_Derivative(Take2(6,MyString))+")";
    if( MyString.size()>=6 && MyString[0]=='a' && MyString[1]=='r' && MyString[2]=='c' && MyString[3]=='c' && MyString[4]=='o' && MyString[5]=='s' )return "((-1/((1-"+Take2(6,MyString)+"^2)^(1/2)))*"+Take_Derivative(Take2(6,MyString))+")";
}
bool Find_X( string MyString )
{
	for( int i=0;i<MyString.size();i++ )
		if( MyString[i]=='x' )return true;
	return false;
}
string Take_Derivative( string MyString )
{
    if( MyString.size()==0 )return "";
	if( canskip(MyString) )
	{
		string NewString="";
		for( int i=1;i<MyString.size()-1;i++ )NewString+=MyString[i];
		return "("+Take_Derivative(NewString)+")";
	}
	if( Number_Operation(MyString)==0 )
	{
		return Derivative(MyString);
	}
	else
	{
		string part1="";
		string part2="";
		char op;
		int Open=0;
		for( int i=0;i<MyString.size();i++ )
		{
		    if( MyString[i]=='(' )Open++;
		    else if( MyString[i]==')' )Open--;

		    if( Open!=0 ){part1+=MyString[i];continue;}

			if( isoperation(MyString[i]) )
			{
				op=MyString[i];
				i++;
				for( i;i<MyString.size();i++ )
					part2+=MyString[i];
				break;
			}
			part1+=MyString[i];
		}
//        cerr<<"TAKING "<<MyString<<"\n"<<part1<<" "<<op<<" "<<part2<<endl;
		part1="("+part1+")";
		part2="("+part2+")";
		if( op=='+' )return "("+Take_Derivative(part1) + "+" + Take_Derivative(part2)+")";
		else if( op=='-' )return "("+Take_Derivative(part1) + "-" + Take_Derivative(part2)+")";
		else if( op=='*' )return "(("+Take_Derivative(part1) + "*" + part2+")"+"+"+"("+part1 + "*" + Take_Derivative(part2)+"))";
		else if( op=='/' )return "((("+Take_Derivative(part1) + "*" + part2+")"+"-"+"("+part1 + "*" + Take_Derivative(part2)+"))/("+part2+"^2))";
		else if( op=='^' )
		{
			if( Find_X(part1) && !Find_X(part2) )
			{
				return "((" + part2 + "*" + part1 + "^" + "(" + part2 + "-1))*" + Take_Derivative(part1) + ")";
			}
			else if( !Find_X(part1) && Find_X(part2) )
			{
				return "((" + part1 + "^" + part2 + ")*ln" + part1 + "*" + Take_Derivative(part2) + ")";
			}
			else if( !Find_X(part1) && !Find_X(part2) )return "(0)";
			else
			{
				return "((" + part1 + "^" + part2 + ")*" + Take_Derivative((part2 + "*" + "ln" + part1)) + ")";
			}
		}
	}
}
string Solve_Exponent( string MyString )
{
    if( MyString.size()==0 )return "";
	if( canskip(MyString) )
	{
		string NewString="";
		for( int i=1;i<MyString.size()-1;i++ )NewString+=MyString[i];
		return "("+Solve_Exponent(NewString)+")";
	}
	if( Number_Operation(MyString)<2 && canskip(MyString)==false )return "("+MyString+")";
	if( Number_Operation(MyString)<2 && canskip(MyString)==true )return MyString;

	string NewString="";
	int Open=0;
	for( int i=MyString.size()-1;i>=0;i-- )
	{
		if( MyString[i]==')' )Open++;
		else if( MyString[i]=='(' )Open--;
		if( Open!=0 )continue;
		if( MyString[i]=='^' )
		{
			int start,end;
			start=i-1;
			int Semiopen=0;
			while( start>=0 && (Semiopen || !isoperation(MyString[start])) )
			{
				if( MyString[start]==')' )Semiopen++;
				else if( MyString[start]=='(' )Semiopen--;
				start--;
			}
			Semiopen=0;
			end=i+1;
			while( end<MyString.size() && (Semiopen || !isoperation(MyString[end])) )
			{
				if( MyString[end]==')' )Semiopen--;
				else if( MyString[end]=='(' )Semiopen++;
				end++;
			}
			string part1="";
			for( int a=0;a<=start;a++ )part1+=MyString[a];
			string part2="";
			for( int a=start+1;a<end;a++ )part2+=MyString[a];
			string part3="";
			for( int a=end;a<MyString.size();a++ )part3+=MyString[a];
			NewString=part1+"("+part2+")"+part3;
			return Solve_Exponent(NewString);
		}
	}
	return "("+MyString+")";
}
string Solve_Division( string MyString )
{
    if( MyString.size()==0 )return "";
	if( canskip(MyString) )
	{
		string NewString="";
		for( int i=1;i<MyString.size()-1;i++ )NewString+=MyString[i];
		return "("+Solve_Division(NewString)+")";
	}
	if( Number_Operation(MyString)<2 && canskip(MyString)==false )return "("+MyString+")";
	if( Number_Operation(MyString)<2 && canskip(MyString)==true )return MyString;
	string NewString="";
	int Open=0;
	for( int i=0;i<(int)MyString.size();i++ )
	{
		if( MyString[i]=='(' )Open++;
		else if( MyString[i]==')' )Open--;
		if( Open!=0 )continue;
		if( MyString[i]=='/' )
		{
			int start,end;
			start=i-1;
			int Semiopen=0;
			while( start>=0 && (Semiopen || !isoperation(MyString[start])) )
			{
				if( MyString[start]==')' )Semiopen++;
				else if( MyString[start]=='(' )Semiopen--;
				start--;
			}
			Semiopen=0;
			end=i+1;
			while( end<MyString.size() && (Semiopen || !isoperation(MyString[end])) )
			{
				if( MyString[end]==')' )Semiopen--;
				else if( MyString[end]=='(' )Semiopen++;
				end++;
			}
			string part1="";
			for( int a=0;a<=start;a++ )part1+=MyString[a];
			string part2="";
			for( int a=start+1;a<end;a++ )part2+=MyString[a];
			string part3="";
			for( int a=end;a<MyString.size();a++ )part3+=MyString[a];
			NewString=part1+"("+part2+")"+part3;
			return Solve_Division(NewString);
		}
	}
	return "("+MyString+")";
}

string Solve_Multiplication( string MyString )
{
    if( MyString.size()==0 )return "";
	if( canskip(MyString) )
	{
		string NewString="";
		for( int i=1;i<MyString.size() - 1;i++ )NewString+=MyString[i];
		return "("+Solve_Multiplication(NewString)+")";
	}
	if (Number_Operation(MyString) < 2 && canskip(MyString) == false) return "(" + MyString + ")";
	if( Number_Operation(MyString) < 2 && canskip(MyString) == true ) return MyString;
	string NewString="";
	int Open=0;
	for( int i=MyString.size()-1;i>=0;i-- )
	{
		if( MyString[i]==')' )Open++;
		else if( MyString[i]=='(' )Open--;

		if( Open!=0 )continue;

		if( MyString[i]=='*' )
		{
			int start,end;
			start=i-1;
			int Semiopen=0;
			while( start>=0 && (Semiopen || !isoperation(MyString[start])) )
			{
				if( MyString[start]==')' )Semiopen++;
				else if( MyString[start]=='(' )Semiopen--;
				start--;
			}
			Semiopen=0;
			end=i+1;
			while( end<MyString.size() && (Semiopen || !isoperation(MyString[end])) )
			{
				if( MyString[end]==')' )Semiopen--;
				else if( MyString[end]=='(' )Semiopen++;
				end++;
			}
			string part1="";
			for( int a=0;a<=start;a++ )part1+=MyString[a];
			string part2="";
			for( int a=start+1;a<end;a++ )part2+=MyString[a];
			string part3="";
			for( int a=end;a<MyString.size();a++ )part3+=MyString[a];
			NewString=part1+"("+part2+")"+part3;
			//cout<<"->"<<NewString<<endl;
			return Solve_Multiplication(NewString);
		}
	}
	return "("+MyString+")";
}

string Solve_Addition( string MyString )
{
    if( MyString.size()==0 )return "";
	if( canskip(MyString) )
	{
		string NewString="";
		for( int i=1;i<MyString.size()-1;i++ )NewString+=MyString[i];
		return "("+Solve_Addition(NewString)+")";
	}
	if( Number_Operation(MyString)<2 && canskip(MyString)==false )return "("+MyString+")";
	if( Number_Operation(MyString)<2 && canskip(MyString)==true )return MyString;
	string NewString="";
	int Open=0;
	for( int i=MyString.size()-1;i>=0;i-- )
	{
		if( MyString[i]==')' )Open++;
		else if( MyString[i]=='(' )Open--;
		if( Open!=0 )continue;
		if( MyString[i]=='+' )
		{
			int start,end;
			start=i-1;
			int Semiopen=0;
			while( start>=0 && (Semiopen || !isoperation(MyString[start])) )
			{
				if( MyString[start]==')' )Semiopen++;
				else if( MyString[start]=='(' )Semiopen--;
				start--;
			}
			Semiopen=0;
			end=i+1;
			while( end<MyString.size() && (Semiopen || !isoperation(MyString[end])) )
			{
				if( MyString[end]==')' )Semiopen--;
				else if( MyString[end]=='(' )Semiopen++;
				end++;
			}
			string part1="";
			for( int a=0;a<=start;a++ )part1+=MyString[a];
			string part2="";
			for( int a=start+1;a<end;a++ )part2+=MyString[a];
			string part3="";
			for( int a=end;a<MyString.size();a++ )part3+=MyString[a];
			NewString=part1+"("+part2+")"+part3;
			//cout<<"->"<<NewString<<endl;
			return Solve_Addition(NewString);
		}
	}
	return "("+MyString+")";
}
string Solve_Subtraction( string MyString )
{
    if( MyString.size()==0 )return "";
	if( canskip(MyString) )
	{
		string NewString="";
		for( int i=1;i<MyString.size()-1;i++ )NewString+=MyString[i];
		return "("+Solve_Subtraction(NewString)+")";
	}
	if( Number_Operation(MyString)<2 && canskip(MyString)==false )return "("+MyString+")";
	if( Number_Operation(MyString)<2 && canskip(MyString)==true )return MyString;
	string NewString="";
	int Open=0;
	for( int i=MyString.size()-1;i>=0;i-- )
	{
		if( MyString[i]==')' )Open++;
		else if( MyString[i]=='(' )Open--;
		if( Open!=0 )continue;
		if( MyString[i]=='-' )
		{
			int start,end;
			start=i-1;
			int Semiopen=0;
			while( start>=0 && (Semiopen || !isoperation(MyString[start])) )
			{
				if( MyString[start]==')' )Semiopen++;
				else if( MyString[start]=='(' )Semiopen--;
				start--;
			}
			Semiopen=0;
			end=i+1;
			while( end<MyString.size() && (Semiopen || !isoperation(MyString[end])) )
			{
				if( MyString[end]==')' )Semiopen--;
				else if( MyString[end]=='(' )Semiopen++;
				end++;
			}
			string part1="";
			for( int a=0;a<=start;a++ )part1+=MyString[a];
			string part2="";
			for( int a=start+1;a<end;a++ )part2+=MyString[a];
			string part3="";
			for( int a=end;a<MyString.size();a++ )part3+=MyString[a];
			NewString=part1+"("+part2+")"+part3;
			//cout<<"->"<<NewString<<endl;
			return Solve_Subtraction(NewString);
		}
	}
	return "("+MyString+")";
}
bool Have_Operation( string MyString )
{
	int Open=0;
	for( int i=0;i<MyString.size();i++ )
	{
		if( MyString[i]=='(' )
			Open++;
		else if( MyString[i]==')' )
			Open--;
		if( Open==0 && isoperation(MyString[i]) )return true;
	}
	return false;
}
string Rebuild( string MyString );
string take( int pos,string MyString )
{
	string result="",result2="";
	int Open=0;
	for( int i=pos;i<MyString.size();i++ )
	{
		if( MyString[i]=='(' )
			Open++;
		else if( MyString[i]==')' )
			Open--;

		result+=MyString[i];
		if( Open==0 )
		{
			for(i=i+1;i<MyString.size();i++)result2+=MyString[i];
			return Rebuild(result)+Rebuild(result2);
		}
	}
	return "";
}
string Rebuild( string MyString )
{
	if(MyString.size()==0)return "";
    if( Number_Operation(MyString)==0 )
    {
        if( MyString.size()>=2 && MyString[0]=='l' && MyString[1]=='n' )return "ln"+(take(2,MyString));
        if( MyString.size()>=2 && MyString[0]=='t' && MyString[1]=='g' )return "tg"+(take(2,MyString));
        if( MyString.size()>=3 && MyString[0]=='s' && MyString[1]=='i' && MyString[2]=='n' )return "sin"+(take(3,MyString));
        if( MyString.size()>=3 && MyString[0]=='c' && MyString[1]=='o' && MyString[2]=='s' )return "cos"+(take(3,MyString));
        if( MyString.size()>=3 && MyString[0]=='c' && MyString[1]=='t' && MyString[2]=='g' )return "ctg"+(take(3,MyString));
        if( MyString.size()>=5 && MyString[0]=='a' && MyString[1]=='r' && MyString[2]=='c' && MyString[3]=='t' && MyString[4]=='g' )return "arctg"+(take(5,MyString));
        if( MyString.size()>=6 && MyString[0]=='a' && MyString[1]=='r' && MyString[2]=='c' && MyString[3]=='c' && MyString[4]=='t' && MyString[5]=='g' )return "arcctg"+(take(6,MyString));
        if( MyString.size()>=6 && MyString[0]=='a' && MyString[1]=='r' && MyString[2]=='c' && MyString[3]=='s' && MyString[4]=='i' && MyString[5]=='n' )return "arcsin"+(take(6,MyString));
        if( MyString.size()>=6 && MyString[0]=='a' && MyString[1]=='r' && MyString[2]=='c' && MyString[3]=='c' && MyString[4]=='o' && MyString[5]=='s' )return "arccos"+(take(6,MyString));
    }
	if( canskip(MyString) )
	{
		string NewString="";
		for( int i=1;i<MyString.size()-1;i++ )NewString+=MyString[i];
		MyString=Rebuild(NewString);
		if( canskip(MyString) )return MyString;
		else return "("+MyString+")";
	}
	if( Have_Operation(MyString)==false )return MyString;
	string part;
	int id=0;
	string result="";
	while( id<MyString.size() )//(x**2+(x**4+1)**(1/3))/ln(x**(x+cos(x))+1)
	{
		part="";
		int Open=0;
		while( id<MyString.size() && (!isoperation(MyString[id]) || Open>0) )
		{
			if( MyString[id]=='(' )
				Open++;
			else if( MyString[id]==')' )
				Open--;
			part+=MyString[id];
			id++;
		}
		result+=Rebuild(part);
		if( id<MyString.size() )
			result=result+MyString[id];
        id++;
	}
	result=Solve_Exponent(result);
	result=Solve_Division(result);
	result=Solve_Multiplication(result);
	result=Solve_Addition(result);
	result=Solve_Subtraction(result);
	MyString=result;
	if( canskip(MyString) )return MyString;
	else return "("+MyString+")";
	return "("+result+")";
}
main()
{
    freopen("deriv.in","r",stdin);
    freopen("deriv.out","w",stdout);
	string MyString="";
	string Just_String="";
	while( getline(cin,Just_String) )
	{
		MyString="";
		for( int i=0;i<(int)Just_String.size();i++ )
		{
			if( Just_String[i]!=' ' )
				MyString+=Just_String[i];
		}
		/*if( MyString=="0" )
		{
			return 0;
		}*/
	    rma++;
		stack<int>st;
		int close[3000]={0};
		int used[3000]={0};
		string result="";
		string result2="";
		int size=MyString.size();
		for( int i=0;i<size;i++ )
		{
			if( i+1<size && MyString[i]==MyString[i+1] && MyString[i]=='*' )
			{
				MyString[i]='^';
				for( int j=i+1;j<size;j++ )
					MyString[j]=MyString[j+1];
				size--;
			}
		}
		for( int i=0;i<size;i++ )
			result+=MyString[i];
		result="("+result+")";
		MyString=result;
		result=Rebuild(MyString);
		result2=Take_Derivative(result);
		for( int i=0;i<result2.size();i++ )
		{
			if( result2[i]=='(' )st.push(i);
			else if( result2[i]==')' )
			{
				close[st.top()]=i;
				st.pop();
			}
		}
		for( int i=0;i<result2.size();i++ )
		{
			if( result2[i]!='(' )continue;
			i++;
			while( i<result2.size() && result2[i]=='(' && close[i]+1==close[i-1] )
			{
				used[i]=1;
				used[close[i]]=1;
				i++;
			}
			i--;
		}
		result="";
		for( int i=0;i<result2.size();i++ )
		{
			if( !used[i] )
			{
				if( result2[i]!='^' )
				result+=result2[i];
				else
				{
					result+="**";
				}
			}
		}
		for( int i=0;i<result.size();i++ )
		{
			if( i<result.size()-1 && result[i]=='(' && result[i+1]==')' ){i++;continue;}
			cout<<result[i];
		}
		cout<<endl;
	}
}


gasdklasjdo
