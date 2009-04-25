package org.dps.servicelayer.dto;

import java.util.Map;
import java.util.Set;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.MapKey;
import javax.persistence.OneToMany;
import javax.persistence.Table;

@Entity
@Table(name="cartstyle")
public class CartStyle extends Audit  {

	@Column(name="cart_style_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long cartStyleID;
	
	@Column(name="name")
	private String name;

	@Column(name="description")
	private String description;
	
	@OneToMany
	@JoinColumn(name="cart_style_id")
    @MapKey(name="key")
	private Map<String, CartStyleProperty> properties;
	

	public Long getCartStyleID() {
		return cartStyleID;
	}

	public Map<String, CartStyleProperty> getProperties() {
		return properties;
	}

	protected void setProperties(Map<String, CartStyleProperty> properties_) {
		properties = properties_;
	}
	
	protected void addProperty(CartStyleProperty property) {
		properties.put(property.getKey(), property);
	}

	public void setCartStyleID(Long cartStyleID_) {
		cartStyleID = cartStyleID_;
	}

	public String getName() {
		return name;
	}

	public void setName(String name_) {
		name = name_;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description_) {
		description = description_;
	}

	
	public String toString() {
		return name;
	}
}
