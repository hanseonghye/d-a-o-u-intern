<%@ page contentType="text/html; charset=utf-8"%>
<%@ page import="java.util.*"%>
<html>
<head>
<title>게시물 상세 보기</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<script>

	function checkBoardDelete(num) {
		//게시글 삭제로직
		location.href='/BoardDelete.do?num='+num;
	}
	function checkReplyDelete(num,renum) {
		//답변 삭제로직
		location.href='/ReplyDelete.do?num='+num+'&renum='+renum;
		alert("댓글을 삭제했습니다.");
		
		
	}
	function checkReplyInsert(form,num) {
		//체크 등록로직
		if(document.getElementById("reply_name").value.length==0){
			alert("댓글 이름을 확인해 주세요.")
		}else if (document.getElementById("reply_contents").value.length==0){
			alert("댓글 내용을 확인해 주세요.")
		}else{
			form.submit();
		}
	}
	function checkBoardUpdate(num) {
		//게시글 수정로직
		location.href="/BoardUpdateForm.do?num="+num;
	}

	
</script>
</head>
<body>
<% List li=(List)request.getAttribute("boardDetail");%>
	<center>
		<h1>게시판</h1>
		<center>
			<table border=1 align=center cellpadding=5 cellspacing=5
				bordercolor="black" bordercolordark="white">
				<tr align="center">
					<td width="80" align="center">번호</td>
					<td width="300" align="center">제목</td>
					<td width="120" align="center">작성자</td>
					<td width="80" align="center">조회수</td>
					<td width="80" align="center">작성일</td>
				</tr>
				<tr align="center">
					<td id="detail_id" width="80" align="center"><%= ((HashMap)li.get(0)).get("NUM") %> </td>
					<td width="300" align="left"> <%= ((HashMap)li.get(0)).get("TITLE") %> </td>
					<td width="120" align="center"><%= ((HashMap)li.get(0)).get("NAME") %></td>
					<td width="80" align="center"><%= ((HashMap)li.get(0)).get("HIT_COUNT") %></td>
					<td width="80" align="center"><%= ((HashMap)li.get(0)).get("REGDATE") %></td>
				</tr>
				<tr>
					<td align=center height=180>내용</td>
					<td colspan=4 align=left valign=top><%= ((HashMap)li.get(0)).get("CONTENTS") %></td>
				</tr>
				<tr>
					<td colspan=5 align=center>
						<a href="BoardList.do">[목록]</a>&nbsp;
						<a href="javascript:checkBoardUpdate(<%=((HashMap)li.get(0)).get("NUM") %>);">[수정]</a>&nbsp;
						<a href="javascript:checkBoardDelete(<%= ((HashMap)li.get(0)).get("NUM") %>);"><span>[삭제]</span></a>
					</td>
				</tr>
			</table>
			<p>
			<table border=1 align=center cellpadding=5 cellspacing=5
				bordercolor="green" bordercolordark="white">
				<tr align="center">
					<td width="80" align="center">번호</td>
					<td width="120" align="center">작성자</td>
					<td width="370" align="center">내용</td>
					<td width="80" align="center">작성일</td>
					<td width="10" align="center">&nbsp;</td>
				</tr>
				<%
					List list1 = (List) request.getAttribute("replyDetail");
// 					답변테이블에서 답변정보 가져오는 로직추가.
				%>
 				<%if ( list1.size() != 0 )
					{ for ( int i=list1.size()-1; i >=0; --i){
				%>
				<tr align="center">
					<td width="80" align="center"><%= ((HashMap)list1.get(i)).get("BOARD_COMMENT_NUM")%></td>
					<td width="120" align="center"><%= ((HashMap)list1.get(i)).get("COMMENT_USERNAME")%></td>
					<td width="370" align="left"><%= ((HashMap)list1.get(i)).get("CONTENTS")%></td>
					<td width="80" align="center"><%= ((HashMap)list1.get(i)).get("COMMENT_REGDATE")%></td>
					<td width="10" align="center"><a href="javascript:checkReplyDelete('<%= ((HashMap)list1.get(i)).get("COMMENT_PARENT")%>','<%= ((HashMap)list1.get(i)).get("COMMENT_NUM")%>')" style="color: red">x</a></td>
				</tr>
					
				<%
					}	} else {
				%>
				<tr>
					<td colspan=5 align=center>댓글이 없습니다.</td>
				</tr>
				<%
					}
				%>
				<tr>
					<form name="insertReply" action="ReplyInsert.do" method="post">
						<input type="hidden" id="parent_num" name="parent_num" value="<%= ((HashMap)li.get(0)).get("NUM") %>">
						<td colspan=5 align=center>이름 : <input type="text" id="reply_name"
							name="reply_name" size=4 maxlenth=6> &nbsp; 댓글 : <textarea id="reply_contents"
								name="reply_contents" cols=35 rows=3></textarea> &nbsp; 
								<input type="button" value="댓글쓰기" onclick="checkReplyInsert(insertReply,<%= ((HashMap)li.get(0)).get("NUM") %>)">
						</td>
					</form>
				</tr>
			</table>
</body>
</html>