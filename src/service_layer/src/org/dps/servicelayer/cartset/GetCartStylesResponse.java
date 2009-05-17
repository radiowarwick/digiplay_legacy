package org.dps.servicelayer.cartset;

import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

import org.dps.servicelayer.dto.CartStyle;

@XmlAccessorType(XmlAccessType.NONE)
public class GetCartStylesResponse {
	
    private List<CartStyleSummary> cartStyles = new LinkedList<CartStyleSummary>();

    public GetCartStylesResponse() {
    	
    }
    
    public GetCartStylesResponse(GetCartStylesRequest request) {
    	
    }

	@XmlElement(name = "cartStyle", required = true)
    @XmlElementWrapper(name="cartStyles", required = true)
	public List<CartStyleSummary> getCartStyles() {
		return cartStyles;
	}
	public void setCartStyles(List<CartStyleSummary> cartStyles_) {
		cartStyles = cartStyles_;
	}
	public void addCartStyle(CartStyle style) { 
		cartStyles.add(new CartStyleSummary(style));
	}
	public void addCartStyle(Collection<CartStyle> styles) {
		for(CartStyle style : styles) {
			cartStyles.add(new CartStyleSummary(style));
		}
	}
	
	@XmlAccessorType(XmlAccessType.NONE)
	public static class CartStyleSummary {
		private Long cartStyleID;
		private String name;
		
		public CartStyleSummary() {
			
		}
		public CartStyleSummary(CartStyle style) {
			cartStyleID = style.getCartStyleID();
			name = style.getName();
		}
		
		@XmlElement(required = true)
		public Long getCartStyleID() {
			return cartStyleID;
		}
		public void setCartStyleID(Long cartStyleID_) {
			cartStyleID = cartStyleID_;
		}
		
		@XmlElement(required = true)
		public String getName() {
			return name;
		}
		public void setName(String name_) {
			name = name_;
		}
		
	}
	
}