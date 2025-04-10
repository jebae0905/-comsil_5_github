#스크립트가 전달받은 인자의 총 개수를 변수 int에 저장
int=$#

#현재까지의 검색결과를 저장할 문자열 초기화
str=""

#예외처리(인자없음)
if [ $# -eq 0 ]
then
	echo Usage:phone searchforp[...searchfor]
		echo"(You didn't tell me what you want to search for)"
fi


#for each parameter
for arg in "$@"
do 
	#첫번째 실행일때 str을 초기화함.
	if [ $int -eq $# ]
	then
		#$()는 쉘 스크립트에서 실행값을 받는 방법임.
		#변수의 값을 대입할때는 "$"이지만, 실행값은 $()
		#파일 mydata에서 첫 번째 인자에 해당하는 패턴을 대소문자 구분 없이 검색한 결과를 str에 저장함.
		str=$(egrep -i "$arg" mydata)
	fi
	
	
	#현재까지의 검색 결과(str)가 비어있지 않으면
	if [ -n "$str" ] 
	then
		#이때까지 구한 사람과 새로운 사람과의 합ㅊ=집합을 구함.
		str=$(egrep -i "$str|$arg" mydata)
	fi

	#--i
	int=`expr $int - 1`

	#출력(int==0)
	if [ $int -eq 0 ]
	then
		#str이 있다면
		if [ -n "$str" ]
		then 
			#awk스크립트로 str전달
			egrep -i "$str" mydata|awk -f display.awk
		fi
	fi
done
