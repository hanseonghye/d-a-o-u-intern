<%@ page contentType="text/html; charset=utf-8"%>
<%@ page import="java.util.*"%>
<html>
<head>
<title>회원정보수정처리</title>
<style type="text/css">
</style>
</head>
<body>
<br><br>
	<% HashMap li=(HashMap)request.getAttribute("boardUpdateDetail");%>

	<table align=center border=1 width="300" cellpadding=5>
	
		<tr>
			<td>
				<p>입력하신 내용대로 수정이 완료되었습니다.</p>
			</td>
		</tr>
		<tr>
			<td>
				<p>수정된 이름 : <%= li.get("name") %></p>
			</td>
		</tr>
		<tr>
			<td>
				<p>수정된 타이틀 : <%= li.get("title") %></p>
			</td>
		</tr>
		<tr>
			<td>
				<p>수정된 내용 : <%= li.get("contents") %></p>
			</td>
		</tr>
		<tr>
				<td align=center><a href="BoardList.do">[목록]</a></td>
		</tr>
	</table>

</body>
</html>
