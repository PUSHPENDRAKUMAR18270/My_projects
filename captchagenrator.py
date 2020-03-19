from PIL import Image,ImageDraw,ImageFont
import random
def getCaptchaText(n=5):

    lower_case=[chr(x) for x in range(97,123)]
    upper_case=[chr(x) for x in range(65,91)]
    digits=[str(x) for x in range(10)]
    all=[lower_case,upper_case,digits]
    captcha=""
    for x in range(n):
        captcha=captcha+random.choice(all[random.randint(0,len(all)-1)])
    return captcha

def makeCaptcha(template,target):
    try:
        #load an image in memory
        # print("hello")
        canvas=Image.open(fp=template)
        #canvas.size=(w,h)
        pen=ImageDraw.Draw(canvas)
        fnt=ImageFont.truetype(font='c:/windows/fonts/forte.ttf',size=40)
        fg_color=237,28,36
        #generate text captcha
        data=getCaptchaText()
        print(data)
        #write it
        reqd_size=pen.textsize(text=data,font=fnt)
        pen.text(xy=((canvas.size[0]-reqd_size[0])/2,(canvas.size[1]-reqd_size[1])/2),text=data,font=fnt,fill=fg_color)
        #save it
        canvas.save(target)
    except:
        print("captcha creation failed")

makeCaptcha('F:\\images\\captchaback.jpg','F:\\images\\new_captcha.jpg')
# def main():
#     print("hello")
# main()
