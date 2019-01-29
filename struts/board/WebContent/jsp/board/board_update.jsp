<%@ page contentType="text/html; charset=utf-8"%>
<%@ page import="java.util.*"%>
<html>
<head>
<title>게시물 작성</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<script>
	function checkModify(form) {
		//입력 유효성 체크 로직 추가
		if(document.getElementById("title").value.length==0){
			alert("제목을 입력해주세요.");
		}else if(document.getElementById("name").value.length==0){
			alert("이름을 입력해주세요.");
		}else if (document.getElementById("contents").value.length==0){
			alert("내용을 입력해 주세요.")
		}else{
			form.submit();
		}
	}
</script>
<link href="http://localhost/bbn/css/base.css" type="text/css" rel="stylesheet" />
<link href="http://localhost/bbn/css/board.css" type="text/css" rel="stylesheet" />

<style>
	td, th {
		height:40px;
	}
	
	td {
		width : 530px;
	}
	
	th {
		width:50px;
	}
</style>

</head>
<body>
	<center>
		<h1>게시판</h1>
		<center>

			<form name="updateform" action="BoardUpdate.do" method="post">
				<% List li=(List)request.getAttribute("boardDetail");%>
				<input type="hidden" name="num" value="<%= ((HashMap)li.get(0)).get("NUM") %>">
				<table  border=1 align=center cellpadding=5 cellspacing=5
					bordercolor="black" bordercolordark="white">
					<tbody>
						<tr>
							<th>제목</th>
							<td colspan=3><input type="text" id="title" name="title" size=20 maxlength=25 style="width: 95%; margin:5px" value="<%= ((HashMap)li.get(0)).get("TITLE") %>"></td>
						</tr>
						
						<tr>
							<th>이름</th>
							<td colspan=3><input type="text" id="name" name="name" size=20 maxlength=25 style="width: 95%; margin:5px " value="<%= ((HashMap)li.get(0)).get("NAME") %>"></td> 
						</tr>
						
						<tr>
							<th>내용</th>
							<td colspan=3 ><textarea  id="contents" name="contents" rows=30 cols=25 style="width: 95%; height: 300px;  margin:5px"><%= ((HashMap)li.get(0)).get("CONTENTS") %></textarea></td>
						</tr>
							<td colspan=4 align=center>
								<a href="javascript:checkModify(updateform)">[수정]</a>&nbsp;
								<a href="BoardDetail.do?num=<%= ((HashMap)li.get(0)).get("NUM") %>"><span>[뒤로가기]</span></a>
							</td>
						<tr>
						
						</tr>
					</tbody>
				<!-- 등록된 데이터를 테이블에 조회후 해당 내용을 수정하여 DBupdate 액션을 호출하도록 추가 -->
				</table>
			</form>
			<%
			%>
		
</body>
</html>