$(document).ready(function(){
	$("#now").css("right", "50%")
	$("#today").css("right", "70%")
	$("#last-week").css("right", "92%")
	console.log($("#now").width())
	$("#indicator").css("width", $("#now").width() + 20 + "px")

	// $("#popup").css({
	// 	"bottom": "-"+$("#popup").height() +"px",
	// 	"tranistion":"0",
	// 	"-webkit-transition":" 0"
	// })


	$(".details").css( "display", "none");
// edit vault
  $( ".edit" ).on( "touchend", function(){
  	console.log("edit:)")
	$("#popup").css("bottom", "0px");
	$(".dimmer").removeClass("off");
	setTimeout(function(){$(".dimmer").removeClass("invisible")}, 3);
  });


  $( ".dimmer" ).on( "touchend", function(){
  	console.log("edit:)")
	// $("#popup").animate({bottom: "-"+$("#popup").height() +"px"}, 200);
	$("#popup").css("bottom", "-"+$("#popup").height() +"px");
	$(".dimmer").addClass("invisible");
	setTimeout(function(){$(".dimmer").addClass("off"); }, 300);
// !!! reset popup
  });


//pay out
$("#pay-out").on("touchend", function(){
	$(".details").css( "display", "block");
	$(".second-level").removeClass("off");
	$(".first-level").addClass("off");
	$("#popup").addClass("expanded");
	$(".popup .handle").css("border-bottom", "none")
	$(this).addClass("small-li")
})

$("#pay-out-to-transport").on("touchend", function(){
	$(".second-level").addClass("off");
	$(".third-level").removeClass("off");
	$("#popup").addClass("pay-out-expanded");
   	$(".enter-payout").focus()

})



$("#pay").on("touchend", function(){
	$("#popup").css("bottom", "-"+$("#popup").height() +"px");
	$(".dimmer").addClass("invisible");
	setTimeout(function(){$(".dimmer").addClass("off")}, 300);
	$("#transfer-notify").addClass("ison");
	setTimeout(function(){$("#transfer-notify").removeClass("ison")},2000)

})


var jobOpened = false;


var initialPos = [0, 0]
var initialY
var initialX
var openCard;

$(document).on("touchstart", function(e){
	initialPos = [e.touches[0].clientX, e.touches[0].clientY];
	initialX = e.touches[0].clientX
	initialY = e.touches[0].clientY
	
})

$(document).on("touchmove", function(e){
	if(jobOpened){
		if (e.touches[0].clientX-initialPos[0] >80 || e.touches[0].clientY - initialPos[1] > 80 ){
			$("nav").css("bottom", "0px");
			$("header").css("top", "0px");
			openCard.find(".card-footer").removeClass("expanded-card");
			openCard.find(".hero-img").removeClass("expanded-card");
			openCard.find(".main-content").removeClass("expanded-card");
			openCard.find(".close-job-button").removeClass("expanded-card");
			$(".content").css({"top": "108px", "bottom": "55px", "padding": "15px"})
			 openCard.removeClass("expanded-job").siblings(".job-card").css("display", "block");
			 openCard.find(".detailed-meta").addClass("off");
			 openCard.find(".floatbox").addClass("off");
			 openCard.find(".edit").removeClass("off");
			 $("#status").css("display", "block")
		}
	
	}
	
	// initialX = e.touches[0].clientX
})




$("#accept-job").on("touchend", function(){
	$(this).addClass("off");
	$("#go-to-jobs").removeClass("off");
	$("#activation-code").removeClass("off");
	$("#job-notify").addClass("ison");
	setTimeout(function(){$("#job-notify").removeClass("ison")},2000)

})


$( ".job-card" ).on("mouseup", function(e){

		// if(Math.abs(e.touches[0].clientY - initialPos[1]) >= 10 ){}else{
	if(jobOpened == false){
		$("nav").css("bottom", "-55px");
		$("header").css("top", "-108px");
		$(this).find(".card-footer").addClass("expanded-card");
		$(this).find(".hero-img").addClass("expanded-card");
		$(this).find(".main-content").addClass("expanded-card");
		$(this).find(".close-job-button").addClass("expanded-card");
		$(".content").css({"top": "0px", "bottom": "0px", "padding": "0", "height": "100vh"})
		$(this).addClass("expanded-job").siblings(".job-card").css("display", "none");
		var currentElement = $(this)
		setTimeout(function(){currentElement.find(".detailed-meta").removeClass("off")}, 100);
		setTimeout(function(){currentElement.find(".floatbox").removeClass("off")}, 100);
		$(this).find(".edit").addClass("off");
		$("#status").css("display", "none")
		jobOpened = true;
		openCard = $(this);
}else{
	// jobOpened = false;
}
// }
}).on('click', '.job-card *', function(e) {
    // clicked on descendant div
    e.stopPropagation();
});




$( ".job-card" ).on("click", function(){
	
	
})

	



/*

TODO

details in pay flow
confirm payment

expanded card view

swipe back


job flow

*/



// graph


var radius = parseInt($("#radius").attr("r")) // Get the radius of the circle 
var perimeter = 2 * 3.14 * radius;

$(".vault-card").each(function(){


	var total = parseFloat($(this).find(".total-amount").html().split('/').pop())
	var saved = parseFloat($(this).find(".saved-amount").html())
  var percentage = saved/total * 100;
  var amount = percentage;
  var fillAmount = perimeter - perimeter * amount / 100;
  
  $(this).find(".progress").attr({
    "stroke-dasharray":perimeter,
    "stroke-dashoffset":fillAmount
  })
  
})



// Tap Styles

  $( "button" ).on( "touchstart", function(event){
    	$( this ).addClass( "tap-button" );
  })
  $( "button" ).on( "touchend", function(event){
    	$( this ).removeClass( "tap-button" );
  })

	$("div.navigation-icon").on("touchstart", function(event){
		$( this ).addClass( "tap-nav" );
	})
	$("div.navigation-icon").on("touchend", function(event){
		$( this ).removeClass( "tap-nav" );
	})

	$("#popup ul li").on("touchstart", function(event){
		$( this ).addClass( "li-highlight" );
	})
	$("#popup ul li").on("touchend", function(event){
		$( this ).removeClass( "li-highlight" );
	})


})

