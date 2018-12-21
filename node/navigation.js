

var initialPos = [0, 0]
var initialX


$(document).on("touchstart", function(e){
	initialPos = [e.touches[0].clientX, e.touches[0].clientY];
	initialX = e.touches[0].clientX
	
})
var isdragging = false

$(document).on("touchmove", function(e){
	
	if (Math.abs(initialPos[0]-e.touches[0].clientX) >55 ){
		isdragging = true

		if (e.touches[0].clientX > initialX){
			if( parseInt($("#ich-bin-ein-div").css("left")) < 0){
				$("#today").css("right",  parseInt($("#today").css("right"), 10) - 1.5 + "px")
				$("#now").css("right",  parseInt($("#now").css("right"), 10) - 1.5 + "px")
				$("#last-week").css("right",  parseInt($("#last-week").css("right"), 10) - 1.5 + "px")
				$("#ich-bin-ein-div").css("left",  parseInt($("#ich-bin-ein-div").css("left"), 10) + 4 + "px")
				$("#noch-ein-div").css("left",  parseInt($("#noch-ein-div").css("left"), 10) + 4 + "px")
			}
			
		}else{
			if( parseInt($("#noch-ein-div").css("left")) > 0){
				$("#today").css("right",  parseInt($("#today").css("right"), 10) + 1.5 + "px")
				$("#now").css("right",  parseInt($("#now").css("right"), 10) + 1.5 + "px")
				$("#last-week").css("right",  parseInt($("#last-week").css("right"), 10) + 1.5 + "px")
				$("#ich-bin-ein-div").css("left",  parseInt($("#ich-bin-ein-div").css("left"), 10) - 4 + "px")
				$("#noch-ein-div").css("left",  parseInt($("#noch-ein-div").css("left"), 10) - 4 + "px")
			}
		}
		
	}else if(initialPos[0]-e.touches[0].clientX < 20 ){}
	
	initialX = e.touches[0].clientX
})

$(document).on("touchend", function(e){
	if(isdragging){
		if (initialPos[0]-initialX < 100){
			$("#today").animate({right:  "50%"}, 300).addClass("active")
				$("#now").animate({right: "30%"}, 300).removeClass("active")
				$("#last-week").animate({right:  "75%"}, 300)
				$("#ich-bin-ein-div").animate({left:  "0px"},300)
					$("#noch-ein-div").animate({left:  "100%"},300)
					$("#indicator").delay(50).animate({width: $("#today").width() + 20 + "px"}, 150)

		}else{
			$("#now").animate({right:  "50%"}, 300).addClass("active")
				$("#today").animate({right: "70%"}, 300).removeClass("active")
				$("#last-week").animate({right:  "92%"}, 300)
				$("#ich-bin-ein-div").animate({left:  "-100%"},300)
					$("#indicator").delay(50).animate({width: $("#now").width() + 20 + "px"}, 150)
					$("#noch-ein-div").animate({left:  "0px"},300)
		}
	}
	isdragging = false
	
				
})