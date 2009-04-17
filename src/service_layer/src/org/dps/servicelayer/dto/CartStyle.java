package org.dps.servicelayer.dto;

import java.util.Set;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.OneToMany;
import javax.persistence.Table;

@Entity
@Table(name="cartstyle")
public class CartStyle extends Audit  {

	@Column(name="cartwall_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long cartwallID;
	
	@Column(name="name")
	private String name;
	
	@Column(name="page")
	private Integer page;
		
	@Column(name="description")
	private String description;
	
	@OneToMany
	@JoinColumn(name="cart_style_id")
	private Set<CartStyleProperty> properties;
	
	
	public Long getCartwallID() {
		return cartwallID;
	}

	public void setCartwallID(Long cartwallID_) {
		cartwallID = cartwallID_;
	}

	public String getName() {
		return name;
	}

	public void setName(String name_) {
		name = name_;
	}

	public Integer getPage() {
		return page;
	}

	public void setPage(Integer page_) {
		page = page_;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description_) {
		description = description_;
	}

	public Set<CartStyleProperty> getProperties() {
		return properties;
	}
	
	public String toString() {
		return name;
	}
}
