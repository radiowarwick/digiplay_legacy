package org.dps.servicelayer.dto;

import java.util.Set;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.OneToMany;
import javax.persistence.Table;

@Entity
@Table(name="cartwall")
public class Cartwall extends Audit  {

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
	
	@ManyToOne
	@JoinColumn(name="cartset_id")
	private Cartset cartset;

	@OneToMany
	@JoinColumn(name="cartwall_id")
	private Set<CartAudio> carts;
	
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

	public Cartset getCartset() {
		return cartset;
	}

	public void setCartset(Cartset cartset_) {
		cartset = cartset_;
	}

	public Set<CartAudio> getCarts() {
		return carts;
	}
	
	public String toString() {
		return name;
	}
}
