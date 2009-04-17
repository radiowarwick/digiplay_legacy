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
@Table(name="cartstyleprop")
public class CartStyleProperty extends Audit  {

	@Column(name="cart_style_prop_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long cartStylePropID;
	
	@Column(name="key")
	private String key;
	
	@Column(name="value")
	private String value;
	
	@ManyToOne
	@JoinColumn(name="cart_style_id")
	private CartStyle style;
	
	public Long getCartStylePropID() {
		return cartStylePropID;
	}

	public void setCartStylePropID(Long cartStylePropID_) {
		cartStylePropID = cartStylePropID_;
	}

	public String getKey() {
		return key;
	}

	public void setKey(String key_) {
		key = key_;
	}

	public String getValue() {
		return value;
	}

	public void setValue(String value_) {
		value = value_;
	}

	public CartStyle getStyle() {
		return style;
	}

	public void setStyle(CartStyle style_) {
		style = style_;
	}

	public String toString() {
		return key + ":" + value;
	}
}
