package org.dps.servicelayer.dto;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@Entity
@Table(name="cartaudio")
@XmlAccessorType(XmlAccessType.NONE)
public class CartAudio extends Audit  {
	
	@Column(name="cart_audio_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long cartAudioID;
	
	@Column(name="cart_id")
	private Integer cartID;
	
	@Column(name="text")
	private String text;
	
	@ManyToOne(fetch = FetchType.LAZY)
	@JoinColumn(name="cartstyle_id")
	private CartStyle style;
	
	@Column(name="cartstyle_id", updatable = false, insertable = false)
	private Long cartStyleID;
	
	@ManyToOne(fetch = FetchType.LAZY)
	@JoinColumn(name="audio_id")
	private Audio audio;
	
	@Column(name="audio_id", updatable = false, insertable = false)
	private Long audioID;
	
	@ManyToOne
	@JoinColumn(name="cartwall_id", nullable=false, insertable=false, updatable=false)
	private Cartwall cartwall;

	@XmlElement(required = true)
	public Long getCartAudioID() {
		return cartAudioID;
	}
	protected void setCartAudioID(Long id) {
		cartAudioID = id;
	}

	@XmlElement(required = true)
	public Integer getCartID() {
		return cartID;
	}
	protected void setCartID(Integer cartID_) {
		cartID = cartID_;
	}

	@XmlElement(required = true)
	public String getText() {
		return text;
	}
	public void setText(String text_) {
		text = text_;
	}

	public CartStyle getStyle() {
		return style;
	}
	public void setStyle(CartStyle style_) {
		style = style_;
	}

	public Audio getAudio() {
		return audio;
	}
	public void setAudio(Audio audio_) {
		audio = audio_;
	}

	public Cartwall getCartwall() {
		return cartwall;
	}
	public void setCartwall(Cartwall cartwall_) {
		cartwall = cartwall_;
	}
	
	@XmlElement(required = true)
	protected Long getAudioID() {
		return audioID;
	}
	protected void setAudioID(Long audioID_) {
		audioID = audioID_;
	}
	
	@XmlElement(required = true)
	public Long getCartStyleID() {
		return cartStyleID;
	}
	public void setCartStyleID(Long cartStyleID_) {
		cartStyleID = cartStyleID_;
	}
	
	public String toString() {
		return text;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((cartAudioID == null) ? 0 : cartAudioID.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		CartAudio other = (CartAudio) obj;
		if (cartAudioID == null) {
			if (other.cartAudioID != null)
				return false;
		} else if (!cartAudioID.equals(other.cartAudioID))
			return false;
		return true;
	}
	
}
