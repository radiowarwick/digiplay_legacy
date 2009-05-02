package org.dps.servicelayer.dto;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.Table;

@Entity
@Table(name="cartaudio")
public class CartAudio extends Audit  {
	
	@Column(name="cart_audio_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long cartAudioID;
	
	@Column(name="cart_id")
	private Integer cartID;
	
	@Column(name="text")
	private String text;
	
	@ManyToOne
	@JoinColumn(name="cartstyle_id")
	private CartStyle style;
	
	@ManyToOne
	@JoinColumn(name="audio_id")
	private Audio audio;
	
	@ManyToOne
	@JoinColumn(name="cartwall_id", nullable=false, insertable=false, updatable=false)
	private Cartwall cartwall;
	
	public Long getCartAudioID() {
		return cartAudioID;
	}

	public Integer getCartID() {
		return cartID;
	}

	protected void setCartID(Integer cartID_) {
		cartID = cartID_;
	}

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
