package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.NONE)
public class AddCartRequest {
    private Long cartwallID;
	private Integer cartID;
	private Long audioID;
	private Long styleID;
	private String text;
	
	@XmlElement(required = true)
	public Long getCartwallID() {
		return cartwallID;
	}
	public void setCartwallID(Long cartwallID_) {
		cartwallID = cartwallID_;
	}

	@XmlElement(required = true)
	public Integer getCartID() {
		return cartID;
	}
	public void setCartID(Integer cartID_) {
		cartID = cartID_;
	}

	@XmlElement(required = true)
	public Long getAudioID() {
		return audioID;
	}
	public void setAudioID(Long audioID_) {
		audioID = audioID_;
	}

	@XmlElement(required = false)
	public Long getStyleID() {
		return styleID;
	}
	public void setStyleID(Long styleID_) {
		styleID = styleID_;
	}

	@XmlElement(required = true)
	public String getText() {
		return text;
	}
	public void setText(String text_) {
		text = text_;
	}
	
}
