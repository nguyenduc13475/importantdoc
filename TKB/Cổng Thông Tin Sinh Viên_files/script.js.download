( function( $ ) {
$( document ).ready(function() {
	$.ajaxSetup({
		headers: {
			'X-CSRF-TOKEN': $('meta[name="_token"]').attr('content')
		}
	});
	$("#jqxLoader").jqxLoader({ width: 100, height: 60, imagePosition: 'top',text: "Đang tải..." });

		$('#jqxTabs').jqxTabs({   width: '100%',position: 'top',  reorder: true,showCloseButtons: true,scrollPosition: 'both' });




$('#cssmenu li.has-sub>a').on('click', function(){
		$(this).removeAttr('href');

		var element = $(this).parent('li');
		if (element.hasClass('open')) {
			element.removeClass('open');
			element.find('li').removeClass('open');
			element.find('ul').slideUp();
		}
		else {
			element.addClass('open');
			element.children('ul').slideDown();
			element.siblings('li').children('ul').slideUp();
			element.siblings('li').removeClass('open');
			element.siblings('li').find('li').removeClass('open');
			element.siblings('li').find('ul').slideUp();
		}
	});

	$('#cssmenu>ul>li.has-sub>a').append('<span class="holder"></span>');

	(function getColor() {
		var r, g, b;
		var textColor = $('#cssmenu').css('color');
		textColor = textColor.slice(4);
		r = textColor.slice(0, textColor.indexOf(','));
		textColor = textColor.slice(textColor.indexOf(' ') + 1);
		g = textColor.slice(0, textColor.indexOf(','));
		textColor = textColor.slice(textColor.indexOf(' ') + 1);
		b = textColor.slice(0, textColor.indexOf(')'));
		var l = rgbToHsl(r, g, b);
		if (l > 0.7) {
			$('#cssmenu>ul>li>a>span').css('border-color', 'rgba(0, 0, 0, .35)');
		}
		else
		{
			$('#cssmenu>ul>li>a>span').css('border-color', 'rgba(255, 255, 255, 1)');
		}
	})();

	function rgbToHsl(r, g, b) {
	    r /= 255, g /= 255, b /= 255;
	    var max = Math.max(r, g, b), min = Math.min(r, g, b);
	    var h, s, l = (max + min) / 2;

	    if(max == min){
	        h = s = 0;
	    }
	    else {
	        var d = max - min;
	        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
	        switch(max){
	            case r: h = (g - b) / d + (g < b ? 6 : 0); break;
	            case g: h = (b - r) / d + 2; break;
	            case b: h = (r - g) / d + 4; break;
	        }
	        h /= 6;
	    }
	    return l;
	}
});
	
	var clicked = false;
	$(document).on('click','.menutab',function (event) {
		$('#jqxLoader').jqxLoader('open');

		

		event.preventDefault();
		event.stopPropagation();
		var link = $(this).attr('data-link');
		if(link.substr(0,4) == 'http'){ window.open(link, "_blank");$('#jqxLoader').jqxLoader('close');return;}
		var title = $(this).attr('data-name');
		//title=title.split('<br>')[0];
		title=title.replace(/<br>/g,'');
		//console.log(title);
		var menuid = $(this).attr('id');
		var id = 'tab-'+ menuid;
		var index = $('#'+id).index();
		var loginas = $(this).attr('data-loginas');

		var datamodule = $(this).attr('data-module');
		if(clicked==true)return;
		clicked = true;
		if(datamodule == 'none' || datamodule == ''){
			$(".menutab[data-link~='" + link + "']").each(function () {
				if(datamodule != $(this).attr('data-module')) {
					menuid = $(this).attr('id');
					id = 'tab-' + menuid;
					index = $('#' + id).index();

				}
			});
		}
		if(menuid=='menu-home') index = 0;
		if(link != null){
		if(index >=0){
			$('#jqxTabs').jqxTabs('select', index);
			clicked=false;
			$('#li-'+menuid).addClass('active');
			$('#li-'+menuid).parents('li').addClass('active');
			$('#jqxLoader').jqxLoader('close');
		}
		else{

			if(link!='#' && link != ''){

				$.ajax({

					url: link,

					success: function (data, status, xhr) {
						var show = true;
						try
						{
							var myobj = JSON.parse(JSON.stringify(data));
							if (myobj.guest) {
								show = false;
								$(location).attr('href','login');

							}
							else if(myobj.norole){
								//bootbox.alert("Không được cấp quyền để truy cập chức năng này");
								bootbox.alert({
									size: "medium",
									title: "Thông báo",
									message: "Không được cấp quyền để truy cập chức năng này!",
									callback: function(){ location.reload(); }
								})
								//return location.reload();
							}

						}
						catch(err){

						}
						if(show) {

							$('#jqxTabs').jqxTabs('addLast', title, data);
							$('#hometabs li:last-child').attr('id', id);
							if(loginas){

								$('#hometabs li:last-child').attr('data-loginas','1');
							}
							$('#page_active').html(title);
							$('#li-'+menuid).addClass('active');
							$('#li-'+menuid).parents('li').addClass('active');
							//$('.content').addClass('isOpen');
							//$('.wrapper').addClass('isOpen1');
							//$('.sidebar').addClass('isClose');
						}
						clicked=false;
						$('#jqxLoader').jqxLoader('close');
					},
					error: function(e, ts, et) { //alert('Lỗi hoặc không tìm thấy nội dung');
						//toastr["error"]("Lỗi hoặc không tìm thấy nội dung, vui lòng refresh lại trang!");
						bootbox.alert('Lỗi hoặc không tìm thấy nội dung, vui lòng refresh lại trang!');
						clicked=false;$('#jqxLoader').jqxLoader('close');
					//	setTimeout('', 8000);
					//	location.reload();
					}
				});
				$('#jqxTabs').jqxTabs('ensureVisible', -1);
			}
			else{clicked=false;	$('#jqxLoader').jqxLoader('close');}
		}
		}

	});
	$('#jqxTabs').on('selected', function (event)
	{
		var selectedTab = event.args.item;
		$('.active').removeClass('active');
		var slid = $('.jqx-tabs-title-selected-top').attr('id');
		var menuid = slid.replace("tab-", "");
		$('#li-'+menuid).addClass('active');
		$('#li-'+menuid).parents('li').addClass('active');
		if(slid =='tab-menu-home')$("#page_active").html("");
		else $("#page_active").html($("#"+slid).text());
	});
	$('#breadcrumb_home').on('click',function(e){
		$('#jqxTabs').jqxTabs('select', 0);
	});
	
} )( jQuery );
