<%@ page contentType="text/html; charset=utf-8"%>
<%@ page import ="java.util.*"%>

<html>
<head>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
<meta http-equiv="content-type" content="text/html; charset=utf-8"/>
<meta name="keywords" content=""/>
<meta name="description" content=""/>
<title>게시물 목록</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<link href="http://localhost/bbn/css/base.css" type="text/css"  rel="stylesheet"/>
<link href="http://localhost/bbn/css/board.css" type="text/css"  rel="stylesheet"/>

<style>
	td, th {
		height:40px;
	}
	
	.red{
		color:red;
		display: inline-block;
		}
</style>


</head>

<body>
 	<form name="listForm" action="" method="post">
		<div class="titWrap01">
			<h1>
				<img src="http://localhost/bbn/img/cs/tit/h1_03_000.gif" alt="게시판"/>
			</h1>
		</div>
		
		<div class="tbWrap01">
			<table id="boardTable" class="List01">
				<caption>게시판</caption>
				<colgroup>
					<col width="9%"/>
					<col width="*"/>
					<col width="14%"/>
					<col width="12%"/>
					<col width="8%"/>
				</colgroup>
				
				<thead>
					<tr>
						<th>번호</th>	
						<th>제목</th>	
						<th>작성자</th>	
						<th>등록일</th>	
						<th class="last">조회수</th>	
					</tr>
				</thead>
				
				<tbody>
				
				<% List li=(List)request.getAttribute("boardList");					
					for (int i=0; i<li.size();++i){
					%>
					<tr>
						<td><%= ((HashMap)li.get(i)).get("NUM")%></td>
						<td><%= ((HashMap)li.get(i)).get("TITLE") %>  [<p class="red"><%= ((HashMap)li.get(i)).get("REPLY_COUNT") %></p>]</td>
						<td><%= ((HashMap)li.get(i)).get("NAME") %></td>
						<td><%= ((HashMap)li.get(i)).get("REGDATE") %></td>
						<td><%= ((HashMap)li.get(i)).get("HIT_COUNT") %></td>
					</tr>
				<% 
					} 
				%>
				
				<%
				for (int i=10;i>li.size();--i){
					%>
					<tr>
						<td></td>
						<td></td>
						<td></td>
						<td></td>
						<td></td>
					</tr>							
					<% 
						}
					%>
				</tbody>
			</table>
			
			<div class="List01">
				<div class="lBtn01">
					<a href="javascript:goBoardList();" class="sbtn0101"><span>새로고침</span></a>
				</div>
				<div class="rBtn04">
					<a href="javascript:goInsertBoard();" class="sbtn0101"><span>글쓰기</span></a>
				</div>
			</div>
			
			
			<div class="List02">
				<input type="text" id="searchKeyword" size=20 maxlength=50   />
				<a href="javascript:goSearchList()" class="sbtn0101"><span>검색</span></a>
			</div>
		
		</div>
	
	</form>
</body>
</html>

<script>


	function goInsertBoard()
	{
		location.href="/jsp/board/board_insert.jsp";
	}
	
	function fnCustDetail(number)
	{
		
	}
	
	function goSearchList()
	{
		location.href="/jsp/board/BoardList.do?search="+document.getElementById('searchKeyword').value;
	}

	
	function goBoardList()
	{
		location.href="/jsp/board/BoardList.do?"
	}
	

	
	$("#boardTable tr").click( function(){
		var tdArr= new Array();
		var tr = $(this);
		var td = tr.children();
		if((td.eq(0).text()).length != 0 )
			location.href="/jsp/board/BoardDetail.do?num="+td.eq(0).text();
	})

	
</script>