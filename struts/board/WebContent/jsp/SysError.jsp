<%--------------------------------------------------------------------------------
  Author      : 김병찬
  Date        : 2008. 9. 1
  Description : 에러공통처리.
  --------------------------- MODIFICATIONLOG ------------------------------------
  Ver  Date            Author       Modification
  0.1  2008. 9. 1       김병찬                파일초기작성
  --------------------------------------------------------------------------------%>
<%@ page contentType="text/html; charset=utf-8" %>
<%
	String site = "bbn";
%>
<script type="text/javascript">
	/*========================================================================*/
	//설명 : 타이틀 변경 
	/*========================================================================*/
	try{
		top.document.title = "에러페이지 | 키움증권";	
	}catch (e){
		if(window.console) console.log(e.description);
	}
		
</script>
<div class="errorWrap">
	<div class="errorBody">
		<div class="errorHeader">
			<div class="errorLogo"><img src="/<%=site%>/img/error/logo.png" alt="키움증권"></div>
		</div>
		
		<div class="cdata mt60">
			<img src="/<%=site%>/img/error/errorText02.gif" alt="죄송합니다. 시스템 내부 오류 입니다.">
		</div>
		
		
		<p class="cdata ment01 mt60">관련 사항은 <span class="pink">키움금융센터(1544-9000)</span>로 문의하여 주십시오.</p>
		
		<div class="errorBottom">COPYRIGHT @2012 KIWOOM SECURITIES CO., LTD. ALL RIGHT RESERVED.</div>
		
	</div>
</div>
