<%@ page contentType="text/html; charset=utf-8"%>
<%@ page import="java.util.*"%>
<html>
<head>
<meta http-equiv="content-type" content="text/html;charset=utf-8" />
<meta name="keywords" content="" />
<meta name="description" content="" />

<title>게시물 목록</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<link href="http://localhost/bbn/css/base.css" type="text/css" rel="stylesheet" />
<link href="http://localhost/bbn/css/board.css" type="text/css" rel="stylesheet" />

<script>
	function fnFormClear(){
		// 다시작성 버튼클릭시
// 		document.getElementsByName("title")[0].value=""
// 		document.getElementsByName("name")[0].value=""
// 		document.getElementsByName("email")[0].value=""
// 		document.getElementsByName("contents")[0].value=""
		location.href="/jsp/board/BoardInsert.do?"
	}
	function goInsertBoard() {
		//게시글 등록
		
		if(document.getElementById("title").value.length==0){
			alert("제목을 입력해주세요.");
		}else if(document.getElementById("name").value.length==0){
			alert("이름을 입력해주세요.");
		}else if (document.getElementById("email").value.length==0){
			alert("이메일을 입력해 주세요.")
		}else if (document.getElementById("contents").value.length==0){
			alert("내용을 입력해 주세요.")
		}else if(!validateEmail(document.getElementById("email").value)){
			alert("이메일 번호를 확인해 주세요.");
		}else{
			var form=document.insertForm;
			var url='/BoardInsert.do?insertChk='+'1';
			form.action=url;
			form.submit();
		}
	}
	
	
	function goBoardList() {
		//목록 이동
		location.href="/jsp/board/BoardList.do?"
	}
	
	function validateEmail(email) 
	{
	    var re = /\S+@\S+\.\S+/;
	    return re.test(email);
	}
	
</script>
</head>
<body>
<div class="titWrap01">
		<h1><img src="http://localhost/bbn/img/cs/tit/h1_03_000.gif" alt="게시판" /></h1>
	</div>
	
	<form name="insertForm" method="post" action="BoardInsert.do" style="width: 839px; ">
		<input type=hidden name="insertChk" value="">
		
		
		<div class="tbWrap01">
		<table class="Write01" summary="게시판 글쓰기 페이지">
		<caption>게시판 글쓰기</caption>
		<colgroup>
		<col width="11%" />
		<col width="45%" />
		<col width="11%" />
		<col width="*" />
		</colgroup>
		<tbody>			
			<tr>
				<th>제목</th>
				<td colspan=3 class="last"><input type="text" id="title" name="title" size=20 maxlength=30 style="width: 98%; "></td>
			</tr>
			<tr>
				<th>이름</th>
				<td colspan=3 class="last"><input type="text" id="name"  name="name" size=8 maxlength=8 style="width: 98%; "></td>
			</tr>
			<tr>
				<th>이메일</th>
				<td colspan=3 class="last"><input type="text" id="email"  name="email" size=20 maxlength=30 style="width: 98%; "></td>
			</tr>
			<tr>
				<th>내용</th>
				<td colspan=3 class="last"><textarea  id="contents" name="contents" rows=30 cols=25 style="width: 97%; height: 300px"></textarea></td>
			</tr>
		
			</table>

			<div class="lBtn01">
				<a href="javascript:goBoardList();" class="sbtn01"><span>목록</span></a>
			</div>
			
			<div class="rBtn04">
				<a href="javascript:fnFormClear();" class="sbtn0101"><span>다시작성</span></a>
				<a href="javascript:goInsertBoard();" class="sbtn01"><span>등록</span></a>
			</div>
		
	</form>
</body>
</html>
